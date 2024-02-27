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
	int	time;

	if (philo->number == philo->table->p_nb && philo->table->p_nb % 2 != 0)
	{
		while (1)
		{
			pthread_mutex_lock(&philo->table->mutex);
			time = get_time(philo);
			if (time >= (philo->hunger * 2))
			{
				pthread_mutex_unlock(&philo->table->mutex);
				return ;
			}
			pthread_mutex_unlock(&philo->table->mutex);
		}
	}
}

void	routine(t_philo *philo)
{
	while (1)
	{
		if (philo->fork[0] == 1)
			philo_eats(philo);
		pthread_mutex_lock(&philo->table->mutex);
		if (philo->exit)
		{
			pthread_mutex_unlock(&philo->table->mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->table->mutex);
		if (philo->fork[0] == 0)
			philo_tries_to_eat(philo);
		pthread_mutex_lock(&philo->table->mutex);
		if (philo->exit)
		{
			pthread_mutex_unlock(&philo->table->mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->table->mutex);
	}
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->mutex);
	pthread_mutex_unlock(&philo->table->mutex);
	wait_two_turns(philo);
	routine(philo);
	return (NULL);
}
