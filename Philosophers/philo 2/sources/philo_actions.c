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

void	philo_eats(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->table->mutex);
	time = get_time(philo);
	philo->food_deadline = time + philo->hunger;
	philo->life_deadline = time + philo->table->tt_die;
	send_msg(philo, "is eating", time);
	pthread_mutex_unlock(&philo->table->mutex);
	while (1)
	{
		pthread_mutex_lock(&philo->table->mutex);
		time = get_time(philo);
		if (im_dead(philo, time))
		{
			pthread_mutex_unlock(&philo->table->mutex);
			return ;
		}
		if (time >= philo->food_deadline)
		{
			philo_sleeps(philo, time);
			return ;
		}
		pthread_mutex_unlock(&philo->table->mutex);
		usleep(2000);
	}
}

void	leaves_both_forks(t_philo *philo)
{
	philo_puts_fork(philo, philo->number - 1, 1);
	if (philo->number != 1)
		philo_puts_fork(philo, philo->number - 2, 0);
	else
		philo_puts_fork(philo, philo->max_number - 1, 0);
}

void	philo_sleeps(t_philo *philo, long time)
{
	philo->meals_left--;
	leaves_both_forks(philo);
	if (!philo->meals_left)
	{
		philo->exit = 1;
		pthread_mutex_unlock(&philo->table->mutex);
		return ;
	}
	philo->sleep_deadline = time + philo->sleepiness;
	send_msg(philo, "is sleeping", time);
	pthread_mutex_unlock(&philo->table->mutex);
	while (1)
	{
		pthread_mutex_lock(&philo->table->mutex);
		time = get_time(philo);
		if (im_dead(philo, time))
		{
			pthread_mutex_unlock(&philo->table->mutex);
			return ;
		}
		if (time >= philo->sleep_deadline)
		{
			philo_thinks(philo, time);
			return ;
		}
		pthread_mutex_unlock(&philo->table->mutex);
		usleep(2000);
	}
}

void	philo_thinks(t_philo *philo, long time)
{
	send_msg(philo, "is thinking", time);
	philo->thinking_deadline = time + philo->thinkingness;
	pthread_mutex_unlock(&philo->table->mutex);
	while (1)
	{
		pthread_mutex_lock(&philo->table->mutex);
		time = get_time(philo);
		if (im_dead(philo, time))
		{
			pthread_mutex_unlock(&philo->table->mutex);
			return ;
		}
		if (time >= philo->thinking_deadline)
		{
			pthread_mutex_unlock(&philo->table->mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->table->mutex);
		usleep(2000);
	}
}