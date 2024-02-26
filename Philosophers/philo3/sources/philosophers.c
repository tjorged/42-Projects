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

void	wait_two_turns(t_philo *philo)
{
	long long	time;

	if (philo->table->p_nb % 2 != 0 && philo->number == philo->table->p_nb)
	{
		pthread_mutex_unlock(&philo->table->mutex);
		while (1)
		{
			time = get_time(philo);
			if (time >= (philo->hunger * 2))
			{
				break ;
			}
			usleep(10);
		}
		pthread_mutex_lock(&philo->table->mutex);
	}
}

void	routine(t_philo *philo)
{
	while (1)
	{
		if (philo->exit || !philo->meals_left)
		{
			break ;
		}
		else if (philo->rfork && philo->lfork)
		{
			philo_eats(philo);
		}
		else if (!philo->rfork && !philo->lfork)
		{
			philo_tries_to_eat(philo);
		}
	}
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->table->error)
		return (pthread_mutex_unlock(&philo->table->mutex), NULL);
	wait_two_turns(philo);
	pthread_mutex_unlock(&philo->table->mutex);
	routine(philo);
	return (NULL);
}
