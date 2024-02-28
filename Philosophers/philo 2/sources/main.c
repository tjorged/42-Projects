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

static void clock_time(t_table *table)
{
	gettimeofday((struct timeval *)table->clock, NULL);
	return (((table->clock->sec * 1000000 + \
	table->clock->mil_sec) - table->start_time) / 1000);
}

static void	health_monitor(t_table *table)
{
	int		i;
	long	time;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&table->philo[i]->mutex);
		time = clock_time(table);
		if (time >= table->philo[i]->deadline)
		{
			pthread_mutex_unlock(&table->philo[i]->mutex);
			break ;
		}
		pthread_mutex_unlock(&table->philo[i]->mutex);
		i++;
		if (i == table->p_nb)
	}
	pthread_mutex_lock(&table->mutex);
	printf("%li %i died\n", time, i + 1);
	table->exit = 1;
	pthread_mutex_unlock(&table->mutex);
}

static void	mutexes_handler(t_table *table, char mode)
{
	long	i;

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
	health_monitor(table);
	if (!threads_joiner(&table, table.p_nb))
		return (end_program(&table, table.p_nb));
	end_program(&table, table.p_nb);
	return (0);
}
