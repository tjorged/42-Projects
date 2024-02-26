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

void better_usleep(t_philo *philo, long time_to_wait)
{
	long	deadline;

	deadline = get_time(philo) + time_to_wait;
	while (1)
	{
		if (get_time(philo) >= deadline)
			break;
		usleep(200);
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

void	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->life_deadline = get_time(philo) + philo->table->tt_die;
	pthread_mutex_unlock(&philo->mutex);
	send_msg(philo, "is eating");
	better_usleep(philo, philo->hunger);
	philo->meals_left--;
	if (!philo->meals_left)
	{
		pthread_mutex_lock(&philo->mutex);
		philo->exit = 1;
		pthread_mutex_unlock(&philo->mutex);
		return ;
	}
	leaves_both_forks(philo);
	philo_sleeps(philo);
}

void	philo_sleeps(t_philo *philo)
{
	send_msg(philo, "is sleeping");
	better_usleep(philo, philo->sleepiness);
	philo_thinks(philo);
}

void	philo_thinks(t_philo *philo)
{
	if (philo->table->p_nb % 2 == 0)
		philo->thinking_deadline = philo->hunger - philo->sleepiness;
	else
		philo->thinking_deadline = (philo->hunger * 2 - philo->sleepiness);
	send_msg(philo, "is thinking");
	better_usleep(philo, philo->thinking_deadline);
}
// ciclo par
// think(protejer negativo), esperar tte - tts

// ciclo impar
// no inicio, ultimo espera: 2(tte)
// think, esperar: 2(tte) - tts
