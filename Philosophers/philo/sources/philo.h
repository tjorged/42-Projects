/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:17:22 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/02/07 14:17:27 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				number;
	int				hp;
	int				hunger;
	bool			eating;
	int				meals_left;
	int				forks;
	int				sleepiness;
	bool			sleeping;
	bool			thinking;
	pthread_t		soul;
	struct s_table	*table;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	struct s_table		*table;
}	t_fork;

typedef struct s_timeval
{
	time_t			sec;
	suseconds_t		mil_sec;
}	t_timeval;

typedef struct s_table
{
	bool		start;
	bool		error;
	int			p_nb;
	int			tt_die;
	int			tt_eat;
	int			tt_sleep;
	int			eating_times;
	int			philo_died;
	t_fork		*fork;
	t_philo		*philo;
	t_timeval	clock;
}	t_table;

//parcer.c
int	parser(t_table *table, int argc, char **argv);

//philo_actions.c
void 	first_dinner(t_philo *philo);

#endif
