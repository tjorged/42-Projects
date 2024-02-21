/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:49:58 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/02/15 17:50:00 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_dies(t_philo *philo, long time)
{
	if (dead_philo(philo))
		return ;
	philo->table->philo_died = 1;
	pthread_mutex_lock(&philo->mutex); 
	philo->exit = 1;
	pthread_mutex_unlock(&philo->mutex);
	printf("%li %i died\n", time, philo->number);
	pthread_mutex_unlock(&philo->table->mutex);
}

void	philo_eats(t_philo *philo)
{
	long	time;

	if (dead_philo(philo))
		return ;
	time = get_time(philo);
	philo->food_deadline = time + philo->hunger;
	printf("%li %i is eating\n", time, philo->number);
	pthread_mutex_unlock(&philo->mutex);
	while (1)
	{
		time = get_time(philo);
		if (time >= philo->life_deadline)
			philo_dies(philo, time);
		else if (time >= philo->food_deadline)
		{
			philo_done_eating(philo, time);
			break ;
		}
		pthread_mutex_lock(&philo->mutex);
		if (philo->exit)
		{
			pthread_mutex_unlock(&philo->mutex);
			break;
		}
		pthread_mutex_unlock(&philo->mutex);
	}
}

void	philo_done_eating(t_philo *philo, long time)
{
	philo->life_deadline = time + philo->hp;
	if (philo->number == philo->max_number && philo->max_number != 1)
		philo_puts_fork(philo, 0, 'r');
	else if (philo->max_number != 1)
		philo_puts_fork(philo, philo->number, 'r');
	philo_puts_fork(philo, philo->number - 1, 'l');
	philo_sleeps(philo);
}

void	philo_sleeps(t_philo *philo)
{
	long		time;

	if (dead_philo(philo))
		return ;
	time = get_time(philo);
	printf("%li %i is sleeping\n", time, philo->number);
	philo->sleep_deadline = time + philo->sleepiness;
	pthread_mutex_unlock(&philo->mutex);
	while (1)
	{
		time = get_time(philo);
		if (time >= philo->life_deadline)
			philo_dies(philo, time);
		else if (time >= philo->sleep_deadline)
		{
			philo_thinks(philo, time);
			break;
		}
		pthread_mutex_lock(&philo->mutex);
		if (philo->exit)
		{
			pthread_mutex_unlock(&philo->mutex);
			break;
		}
		pthread_mutex_unlock(&philo->mutex);
	}
}

void	philo_thinks(t_philo *philo, long time)
{
	if (dead_philo(philo))
		return ;
	printf("%li %i is thinking\n", time, philo->number);
	pthread_mutex_unlock(&philo->table->mutex);
}