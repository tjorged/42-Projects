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

long	get_time(t_philo *philo)
{
	gettimeofday((struct timeval *)philo->watch, NULL);
	return ((philo->watch->sec * 1000000 + \
		philo->watch->mil_sec) / 1000 - philo->birth_time);
}

static void	first_dinner(t_philo *philo)
{
	if (philo->number % 2 != 0)
	{
		if (philo->number == philo->max_number)
			philo_takes_fork(philo, 0);
		else
			philo_takes_fork(philo, philo->number);
		philo_takes_fork(philo, philo->number - 1);
	}
	else
		philo_thinks(philo);
}

void	routine(t_philo *philo)
{
	while (1)
	{
		if (philo->forks == 2)
			philo_eats(philo);
		else
			philo_thinks(philo);
		if (get_time(philo) >= 1500 || !philo->alive)
		{
			printf("ACABOU!(%i)\n", philo->number);
			break ;
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
	philo->birth_time = philo->table->start_time;
	philo->life_deadline = get_time(philo) + philo->table->tt_die;
	pthread_mutex_unlock(&philo->table->mutex);
	first_dinner(philo);
	routine(philo);
	return (NULL);
}
