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
	int					exit;
	long				life_deadline;
	long				food_deadline;
	long				sleep_deadline;
	long				thinking_deadline;
	long				birth_time;
	long				hunger;
	long				sleepiness;
	long				thinkingness;
	int					meals_left;
	int					fork[2];
	pthread_t			soul;
	t_timeval			*watch;
	struct s_table		*table;
	pthread_mutex_t		mutex;
}	t_philo;

typedef struct s_fork
{
	int					taken;
	struct s_table		*table;
	pthread_mutex_t		mutex;
}	t_fork;

typedef struct s_table
{
	long				start_time;
	int					p_nb;
	long				tt_die;
	long				tt_eat;
	long				tt_sleep;
	int					eating_times;
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
void	kill_all_philos(t_table *table);
int		send_msg(t_philo *philo, char *msg, long time);
void	philo_dies(t_philo *philo, long time);
int		im_dead(t_philo *philo, long time);
int		has_both_forks(t_philo *philo);
void	philo_tries_to_eat(t_philo *philo);
void	philo_takes_fork(t_philo *philo, int fork_nb, int hand);
void	philo_puts_fork(t_philo *philo, int fork_nb, int hand);

//philo_actions.c
int		is_philo_dead(t_philo *philo, long time);
void	philo_dies(t_philo *philo, long time);
void	philo_eats(t_philo *philo);
void	philo_done_eating(t_philo *philo, long time);
void	philo_sleeps(t_philo *philo, long time);
void	philo_thinks(t_philo *philo, long time);

//philosophers.c
void	*philo_life(void *arg);
#endif
