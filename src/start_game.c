#include "matches.h"

static void		init_game(void)
{
	game.state = NB_MATCHES;
	game.n_state = NB_MATCHES;
	game.winner = 0;
	if (rand() % 2 == 0)
		game.turn = 1;
	else
		game.turn = 2;
}

static void		display(void)
{
	size_t		i;

	i = 0;
	while (i < game.state)
	{
		ft_printf(" | ");
		i++;
	}
	ft_printf(" (%d)\n", i);
}

static size_t	step(size_t action)
{
	if (action < 1 || action > 3)
	{
		ft_printf("action not allowed : %d\n", action);
		exit(0);
	}
	if (game.state <= action)
	{
		game.n_state = 0;
		return (-1);
	}
	else
	{
		game.n_state -= action;
		return (0);
	}
}

static void		train_player(size_t p)
{
	size_t		i;
	size_t		state;
	size_t		n_state;
	int			reward;

	if (player[p].trainable == 1 && player[p].human == 0)
	{
		i = 1;
		while (player[p].nb_hist >= i)
		{
			state = player[p].hist[player[p].nb_hist - i].s;
			n_state = player[p].hist[player[p].nb_hist - i].ns;
			reward = player[p].hist[player[p].nb_hist - 1].r;
			if (reward == 0)
				player[p].V[state] = player[p].V[state] + 0.001 * (player[p].V[n_state] - player[p].V[state]);
            else if (reward == -1)
				player[p].V[state] = player[p].V[state] - (0.001 * player[p].V[state]);
			else if (reward == 1)
				player[p].V[state] = player[p].V[state] + 0.001 * (1.00 - player[p].V[state]);
			i++;
		}
	}
}

static size_t		greedy_step(size_t p)
{
	size_t		a;
	size_t		i;
	double		vmin;
	size_t		vi;

	i = 0;
	vi = 4;
	vmin = 10.00;
	while (i < 3)
	{
		a = i + 1;
		if (game.state > a && (i == 0 || vmin > player[p].V[game.state - a]))
		{
			vmin = player[p].V[game.state - a];
			vi = i;
		}
		i++;
	}
	if (vi != 4)
		return (vi + 1);
	return (1);
}

_Bool		start_game(size_t p1, size_t p2, _Bool train)
{
	size_t		action;
	size_t		x;
	int			reward;
	double		tmp;
	char		c;
	char		*str;

	str = NULL;
	init_game();
	x = 0;
	if ((game.turn == 2 && player[p1].human == TRUE) ||
		(game.turn == 1 && player[p2].human == TRUE))
		display();
	while (game.winner == 0)
	{
		if ((game.turn == 1 && player[p1].human == TRUE) ||
			(game.turn == 2 && player[p2].human == TRUE))
		{
			display();
			action = 0;
			while (action < 1 || action > 3)
			{
				if (!(str = malloc(sizeof(*str) * 1001)))
					return (0);
				fgets(str, 1000, stdin);
				if (!str)
					return(TRUE);
				c = str[0];
				free(str);
				str = NULL;
				if (c >= '0' && c <= '9')
					action = c - '0';
				else if (c == 'x')
					return (TRUE);
				else
					action = 0;
			}
		}
		else
		{
			tmp = (rand() % 10000) / 10000.00;
			if (game.turn == 1)
			{
				if (player[p1].eps >= tmp)
					action = rand() % 3 + 1;
				else
					action = greedy_step(p1);
			}
			else
			{
				if (player[p2].eps >= tmp)
					action = rand() % 3 + 1;
				else
					action = greedy_step(p2);
			}
		}
		if (action > game.state)
			action = game.state;
		reward = step(action);
		if ((game.turn == 1 && player[p1].human == FALSE && player[p2].human == TRUE) ||
			(game.turn == 2 && player[p2].human == FALSE && player[p1].human == TRUE))
			ft_printf("IA action = %d\n", action);
		if (game.turn == 1)
		{
			if (x != 0)
			{
				player[p2].hist[player[p2].nb_hist - 1].r = reward * -1;
				player[p2].hist[player[p2].nb_hist - 1].ns = game.n_state;
			}
			player[p1].hist[player[p1].nb_hist].s = game.state;
			player[p1].hist[player[p1].nb_hist].a = action;
			player[p1].hist[player[p1].nb_hist].r = reward;
			player[p1].hist[player[p1].nb_hist].ns = 0;
			player[p1].nb_hist++;
		}
		else
		{
			if (x != 0)
			{
				player[p1].hist[player[p1].nb_hist - 1].r = reward * -1;
				player[p1].hist[player[p1].nb_hist - 1].ns = game.n_state;
			}
			player[p2].hist[player[p2].nb_hist].s = game.state;
			player[p2].hist[player[p2].nb_hist].a = action;
			player[p2].hist[player[p2].nb_hist].r = reward;
			player[p2].hist[player[p2].nb_hist].ns = 0;
			player[p2].nb_hist++;
		}
		game.state = game.n_state;
		if (((game.turn == 1 && player[p1].human == TRUE) || (game.turn == 2 && player[p2].human == TRUE)) && action > 0 && action < 4)
			display();
		game.turn = game.turn % 2 + 1;
		if (game.state == 0)
			game.winner = game.turn;
		x++;
	}
	if (train == TRUE)
	{
		if (player[p1].trainable == TRUE)
			train_player(p1);
		if (player[p2].trainable == TRUE)
			train_player(p2);
	}
	player[p1].nb_hist = 0;
	player[p2].nb_hist = 0;
	return (FALSE);
}
