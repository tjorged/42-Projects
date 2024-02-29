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

static void	philo_thinks(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->table->mutex);
	time = get_time(philo);
	if (!send_msg(philo, "is thinking", time))
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->table->mutex);
	better_usleep(philo, time + philo->thinkingness);
}

static void	leaves_both_forks(t_philo *philo)
{
	philo_leaves_fork(philo, philo->number - 1, 1);
	if (philo->number != 1)
		philo_leaves_fork(philo, philo->number - 2, 0);
	else
		philo_leaves_fork(philo, philo->max_number - 1, 0);
}

static void	philo_sleeps(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->table->mutex);
	time = get_time(philo);
	philo->meals_left--;
	leaves_both_forks(philo);
	if (philo->meals_left == 0)
	{
		philo->exit = 1;
		pthread_mutex_lock(&philo->mutex);
		philo->full = 1;
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(&philo->table->mutex);
		return ;
	}
	if (!send_msg(philo, "is sleeping", time))
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->table->mutex);
	better_usleep(philo, time + philo->sleepiness);
	philo_thinks(philo);
}

void	philo_eats(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->table->mutex);
	pthread_mutex_lock(&philo->mutex);
	time = get_time(philo);
	philo->life_deadline = time + philo->table->tt_die;
	pthread_mutex_unlock(&philo->mutex);
	if (!send_msg(philo, "is eating", time))
	{
		leaves_both_forks(philo);
		pthread_mutex_unlock(&philo->table->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->table->mutex);
	better_usleep(philo, time + philo->hunger);
	philo_sleeps(philo);
}
