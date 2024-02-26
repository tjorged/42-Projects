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
	long long	time;

	pthread_mutex_lock(&philo->table->mutex);
	if (philo->exit || !philo->meals_left)
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return ;
	}
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
			break;
		}
		else if (time >= philo->food_deadline)
		{
			pthread_mutex_unlock(&philo->table->mutex);
			philo_sleeps(philo);
			break ;
		}
		pthread_mutex_unlock(&philo->table->mutex);
	}
}

void	leaves_both_forks(t_philo *philo)
{
	if (philo->number == philo->max_number && philo->max_number != 1)
		philo_puts_fork(philo, 0, 'r');
	else if (philo->max_number != 1)
		philo_puts_fork(philo, philo->number, 'r');
	philo_puts_fork(philo, philo->number - 1, 'l');
}

void	philo_sleeps(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->table->mutex);
	philo->meals_left--;
	if (!philo->meals_left)
			philo->exit = 1;
	leaves_both_forks(philo);
	if (philo->exit || !philo->meals_left)
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return ;
	}
	time = get_time(philo);
	send_msg(philo, "is sleeping", time);
	philo->sleep_deadline = time + philo->sleepiness;
	pthread_mutex_unlock(&philo->table->mutex);
	while (1)
	{
		pthread_mutex_lock(&philo->table->mutex);
		time = get_time(philo);
		if (im_dead(philo, time))
		{
			pthread_mutex_unlock(&philo->table->mutex);
			break;
		}
		else if (time >= philo->sleep_deadline)
		{
			pthread_mutex_unlock(&philo->table->mutex);
			philo_thinks(philo);
			break;
		}
		pthread_mutex_unlock(&philo->table->mutex);
	}
}

void	philo_thinks(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->table->mutex);
	if (philo->exit || !philo->meals_left)
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return ;
	}
	time = get_time(philo);
	send_msg(philo, "is thinking", time);
	if (philo->table->p_nb % 2 == 0)
		philo->thinking_deadline = time + philo->hunger - philo->sleepiness;
	else
		philo->thinking_deadline = time + (philo->hunger * 2 - philo->sleepiness);
	pthread_mutex_unlock(&philo->table->mutex);
	while (1)
	{
		pthread_mutex_lock(&philo->table->mutex);
		time = get_time(philo);
		if (im_dead(philo, time))
		{
			pthread_mutex_unlock(&philo->table->mutex);
			break;
		}
		else if (time >= philo->thinking_deadline)
		{
			pthread_mutex_unlock(&philo->table->mutex);
			break;
		}
		pthread_mutex_unlock(&philo->table->mutex);
	}
}
// ciclo par
// think(protejer negativo), esperar tte - tts

// ciclo impar
// no inicio, ultimo espera: 2(tte)
// think, esperar: 2(tte) - tts
