#ifndef MATCHES_H
 #define MATCHES_H

#include "ft_printf.h"
#include <time.h>

#define NB_MATCHES 21
#define TRUE 1
#define FALSE 0

typedef	struct 	s_hist
{
	size_t		s;
	size_t		a;
	int			r;
	size_t		ns;
}				t_hist;

typedef	struct 	s_player
{
	_Bool		human;
	_Bool		trainable;
	t_hist		hist[NB_MATCHES];
	size_t		nb_hist;
	double		eps;
	double		V[NB_MATCHES + 1];
}				t_player;

typedef	struct 	s_game
{
	size_t		state;
	size_t		n_state;
	size_t		turn;
	size_t		winner;
}				t_game;


t_player	player[4];
t_game		game;

_Bool		start_game(size_t p1, size_t p2, _Bool train);

#endif