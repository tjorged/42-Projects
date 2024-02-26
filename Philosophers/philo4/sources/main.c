/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:17:14 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/02/07 14:17:16 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_all_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->p_nb)
	{
		pthread_mutex_lock(&table->philo[i].mutex);
		table->philo[i].exit = 1;
		pthread_mutex_unlock(&table->philo[i].mutex);
	}
}

void check_for_dead_philos(t_table *table)
{
	int			i;
	long	time;

	while(1)
	{
		i = 0;
		gettimeofday((struct timeval *)table->clock, NULL);
		time = ((table->clock->sec * 1000000 + \
			table->clock->mil_sec) - table->start_time) / 1000;
		while (i < table->p_nb)
		{
			pthread_mutex_lock(&table->philo[i].mutex);
			if (time >= table->philo[i].life_deadline)
			{
				pthread_mutex_unlock(&table->philo[i].mutex);
				pthread_mutex_lock(&table->mutex);
				printf("%li %i %s\n", time, i + 1, "died");
					table->end = 1;
				kill_all_philos(table);
					pthread_mutex_unlock(&table->mutex);
				return ;
			}
			pthread_mutex_unlock(&table->philo[i].mutex);
			i++;
		}
		usleep(100);
	}
}

static void	mutexes_handler(t_table *table, char mode)
{
	int	i;

	i = -1;
	if (mode == 'c')
	{
		while (++i < table->p_nb)
		{
			pthread_mutex_init(&table->fork[i].mutex, NULL);
			pthread_mutex_init(&table->philo[i].mutex, NULL);
		}
		pthread_mutex_init(&table->mutex, NULL);
	}
	else if (mode == 'd')
	{
		while (++i < table->p_nb)
		{
			pthread_mutex_destroy(&table->fork[i].mutex);
			pthread_mutex_destroy(&table->philo[i].mutex);
		}
		pthread_mutex_destroy(&table->mutex);
	}
	return ;
}

int	end_program(t_table *table, int limiter)
{
	int	i;

	i = -1;
	while (++i < limiter)
		free(table->philo[i].watch);
	mutexes_handler(table, 'd');
	free(table->philo);
	free(table->fork);
	free(table->clock);
	return (0);
}

int	main(int argc, char **argv)
{
	static t_table	table;

	if (!parser(&table, argc, argv))
		return (0);
	mutexes_handler(&table, 'c');
	if (!threads_creator(&table))
		return (end_program(&table, table.p_nb));
	check_for_dead_philos(&table);
	if (!threads_joiner(&table, table.p_nb))
		return (end_program(&table, table.p_nb));
	end_program(&table, table.p_nb);
	return (0);
}
