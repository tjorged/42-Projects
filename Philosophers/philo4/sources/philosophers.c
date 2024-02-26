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
	if (philo->max_number % 2 != 0 && philo->number == philo->max_number)
		better_usleep(philo, philo->hunger * 2);
}

void	routine(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->exit || !philo->meals_left)
		{
			pthread_mutex_unlock(&philo->mutex); 
			break ;
		}
		pthread_mutex_unlock(&philo->mutex);
		if (!philo->rfork && !philo->lfork)
			philo_tries_to_eat(philo);
		else if (philo->rfork && philo->lfork)
			philo_eats(philo);
	}
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->table->error)
		return (pthread_mutex_unlock(&philo->table->mutex), NULL);
	pthread_mutex_unlock(&philo->table->mutex);
	wait_two_turns(philo);
	routine(philo);
	return (NULL);
}
