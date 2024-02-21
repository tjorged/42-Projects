/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:49:34 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/02/15 17:49:42 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *philo)
{
	while (1)
	{	
		pthread_mutex_lock(&philo->mutex);
		if (philo->exit)
		{
			printf("ACABOU!(%i)\n", philo->number);
			if (philo->rfork)
			{
				if (philo->number == philo->max_number && philo->max_number != 1)
					philo_puts_fork(philo, 0, 'r');
				else if (philo->max_number != 1)
					philo_puts_fork(philo, philo->number, 'r');
			}
			if (philo->lfork)
				philo_puts_fork(philo, philo->number - 1, 'l');
			pthread_mutex_unlock(&philo->mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex);
		if (philo->rfork && philo->lfork)
		{
			philo_eats(philo);
		}
		else if (!philo->rfork && !philo->lfork)
		{
			philo_tries_to_eat(philo);
		}
	}
	printf("acabou a thread!\n");
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->mutex);
	pthread_mutex_lock(&philo->mutex);
	if (philo->table->error)
	{
		return (pthread_mutex_lock(&philo->mutex), \
		pthread_mutex_unlock(&philo->table->mutex), NULL);
	}
	philo->birth_time = philo->table->start_time;
	philo->life_deadline = get_time(philo) + philo->table->tt_die;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->table->mutex);
	routine(philo);
	return (NULL);
}
