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

static void	wait_two_turns(t_philo *philo)
{
	if (philo->number == philo->max_number \
				&& philo->max_number % 2 != 0 \
				&& philo->number != 1)
		better_usleep(philo, get_time(philo) + (philo->hunger * 2));
}

static void	philo_tries_to_eat(t_philo *philo)
{
	if (philo->number % 2 != 0)
	{
		if (philo->number != 1)
			philo_takes_fork(philo, philo->number - 2, 0);
		else
			philo_takes_fork(philo, philo->max_number - 1, 0);
		if (philo->max_number != 1)
			philo_takes_fork(philo, philo->number - 1, 1);
	}
	else
	{
		philo_takes_fork(philo, philo->number - 1, 1);
		philo_takes_fork(philo, philo->number - 2, 0);
	}
}

static void	routine(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->table->mutex);
		if (philo->table->exit || philo->exit)
		{
			pthread_mutex_unlock(&philo->table->mutex);
			return ;
		}
		else if (philo->fork[0] && philo->fork[1])
		{
			pthread_mutex_unlock(&philo->table->mutex);
			philo_eats(philo);
		}
		else if (!philo->fork[0])
		{
			pthread_mutex_unlock(&philo->table->mutex);
			philo_tries_to_eat(philo);
		}
		else
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
