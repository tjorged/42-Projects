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

typedef struct s_timeval
{
	time_t			sec;
	suseconds_t		mil_sec;
}	t_timeval;

typedef struct s_philo
{
	int					number;
	int					max_number;
	long				hp;
	bool				exit;
	pthread_mutex_t		mutex;
	long				life_deadline;
	long				birth_time;
	long				hunger;
	bool				eating;
	long				food_deadline;
	int					meals_left;
	bool				lfork;
	bool				rfork;
	bool				waiting_lfork;
	bool				waiting_rfork;
	long				wating_starvation;
	long				sleepiness;
	bool				sleeping;
	long				sleep_deadline;
	bool				thinking;
	pthread_t			soul;
	t_timeval			*watch;
	struct s_table		*table;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	struct s_table		*table;
}	t_fork;

typedef struct s_table
{
	long				start_time;
	bool				error;
	int					p_nb;
	int					tt_die;
	int					tt_eat;
	int					tt_sleep;
	int					eating_times;
	int					philo_died;
	t_fork				*fork;
	t_philo				*philo;
	t_timeval			*clock;
	pthread_mutex_t		mutex;
}	t_table;

//main.c
int		end_program(t_table *table, int limiter);

//parcer.c
int		parser(t_table *table, int argc, char **argv);

//threads.c
int		threads_joiner(t_table *table, int limiter);
int		threads_creator(t_table *table);

//philosophers.c
void	*philo_life(void *arg);

//philo_utils.c
long	get_time(t_philo *philo);
int		dead_philo(t_philo *philo);
void	philo_tries_to_eat(t_philo *philo);
void	philo_takes_fork(t_philo *philo, int fork_nb, char hand);
void	philo_puts_fork(t_philo *philo, int fork_nb, char hand);

//philo_actions.c
void	philo_dies(t_philo *philo, long time);
void	philo_eats(t_philo *philo);
void	philo_done_eating(t_philo *philo, long time);
void	philo_sleeps(t_philo *philo);
void	philo_thinks(t_philo *philo, long time);

//philosophers.c
void	*philo_life(void *arg);
void	kill_all_philos(t_table *table);
#endif
