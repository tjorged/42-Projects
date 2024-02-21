/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:48:44 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/02/15 17:48:51 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_joiner(t_table *table, int limiter)
{
	int		i;
	char	*error_msg;

	error_msg = "Error: Something went wrong while joining a thread\n";
	i = -1;
	while (++i < limiter)
	{
		if (pthread_join(table->philo[i].soul, NULL) != 0)
		{
			write(2, error_msg, 52);
			table->error = 1;
			return (0);
		}
	}
	return (1);
}

int	threads_creator(t_table *table)
{
	char	*error_msg;
	int		i;

	error_msg = "Error: Something went wrong while creating a thread\n";
	i = -1;
	pthread_mutex_lock(&table->mutex);
	while (++i < table->p_nb)
	{
		if (pthread_create(&table->philo[i].soul, NULL, \
		&philo_life, &table->philo[i]) != 0)
		{
			write(2, error_msg, 53);
			table->error = 1;
			pthread_mutex_unlock(&table->mutex);
			return (0);
		}
	}
	gettimeofday((struct timeval *)table->clock, NULL);
	table->start_time = (table->clock->sec * 1000000 \
		+ table->clock->mil_sec) / 1000;
	pthread_mutex_unlock(&table->mutex);
	return (1);
}
