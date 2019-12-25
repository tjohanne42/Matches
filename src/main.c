#include "matches.h"

static void		init_player(size_t p, _Bool is_human, _Bool is_trainable)
{
	size_t		i;

	i = 0;
	player[p].human = is_human;
	player[p].trainable = is_trainable;
	player[p].eps = 0.9999;
	player[p].nb_hist = 0;
	while (i < NB_MATCHES + 1)
	{
		player[p].V[i] = 0.50;
		player[p].V[i] = 0.50;
		i++;
	}
}

int		main(void)
{
	size_t		i;
	size_t		win;
	size_t		lose;
	size_t		win2;
	size_t		lose2;
	size_t		win3;
	size_t		lose3;

	i = 0;
	if (NB_MATCHES < 2)
	{
		ft_printf("Invalid NB_MATCHES : defined in \"inc/matches.h\"\n");
		return (0);
	}
	srand(time(NULL));
	init_player(0, FALSE, TRUE);
	init_player(1, FALSE, TRUE);
	init_player(2, FALSE, FALSE);
	init_player(3, TRUE, FALSE);
	while (i < 100000)
	{
		if (i % 10 == 0 && i != 0)
		{
			player[0].eps = player[0].eps * 0.9996;
			if (player[0].eps < 0.05)
				player[0].eps = 0.05;
            player[1].eps = player[1].eps * 0.9996;
            if (player[1].eps < 0.05)
				player[1].eps = 0.05;
		}
		start_game(0, 1, TRUE);
		i++;
	}
	i = 0;
	player[0].eps = 0.00;
	player[2].eps = 100.00;
	win = 0;
	lose = 0;
	while (i < 1000)
	{
		start_game(0, 2, FALSE);
		if (game.winner == 1)
			win++;
		else if (game.winner == 2)
			lose++;
		i++;
	}
	win2 = 0;
	lose2 = 0;
	win3 = 0;
	lose3 = 0;
	i = 0;
	player[1].eps = 0.00;
	while (i < 1000)
	{
		start_game(0, 1, FALSE);
		if (game.winner == 1)
			win3++;
		else if (game.winner == 2)
			lose3++;
		i++;
	}
	_Bool		EXIT_VALUE;

	EXIT_VALUE = FALSE;
	while (!EXIT_VALUE)
	{
		system("clear");
//		ft_printf("winrate vs random : %f%%\n", (double)win / ((double)win + (double)lose) * 100);
//		ft_printf("winrate vs another IA : %f%%\n", (double)win3 / ((double)win3 + (double)lose3) * 100);
		if (win2 != 0 || lose2 != 0)
			ft_printf("winrate vs player : %f%%\n\n", (double)win2 / ((double)win2 + (double)lose2) * 100);
		ft_printf("Rules : game starts with %d matches\n\tplayers will take 1,2 or 3 matches at their turns.\n\t", NB_MATCHES);
		ft_printf("player who takes last matche lose\n\tenter 'x' to exit\n\n");
/*		i = 1;
		while (i < NB_MATCHES + 1)
		{
			ft_printf("V%d : %f\n", i, player[1].V[i]);
			i++;
		}*/
		EXIT_VALUE = start_game(0, 3, FALSE);
		if (!EXIT_VALUE)
		{
			if (game.winner == 2)
			{
				ft_printf("Player win\n");
				lose2++;
			}
			else
			{
				win2++;
				ft_printf("IA win\n");
			}
			fgetc(stdin);
		}
	}
	return (0);
}
