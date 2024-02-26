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

void	clock_refresh(t_table *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->mutex);
		gettimeofday((struct timeval *)table->clock, NULL);
		table->current_time =((table->clock->sec * 1000000 + \
			table->clock->mil_sec) - table->start_time) / 1000;
		if (table->error)
		{
			table->current_time = 0;
			break;
		}
		pthread_mutex_unlock(&table->mutex);
		usleep(10);
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
	clock_refresh(&table);
	if (!threads_joiner(&table, table.p_nb))
		return (end_program(&table, table.p_nb));
	end_program(&table, table.p_nb);
	return (0);
}
