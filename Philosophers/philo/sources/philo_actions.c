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

void	philo_thinks(t_philo *philo)
{
	long		time;

	time = get_time(philo);
	printf("%li %i is thinking\n", get_time(philo), philo->number);
	if (philo->number % 2 != 0)
	{
		if (philo->number == philo->max_number)
			philo_takes_fork(philo, 0);
		else
			philo_takes_fork(philo, philo->number);
		philo_takes_fork(philo, philo->number - 1);
	}
	if (philo->number % 2 == 0)
	{
		philo_takes_fork(philo, philo->number - 1);
		if (philo->number == philo->max_number)
			philo_takes_fork(philo, 0);
		else
			philo_takes_fork(philo, philo->number);
	}
}

void	philo_takes_fork(t_philo *philo, int fork_nb)
{
	pthread_mutex_lock(&philo->table->fork[fork_nb].mutex);
	philo->forks++;
	printf("%li %i has taken a fork\n", get_time(philo), philo->number);
}

void	philo_puts_fork(t_philo *philo, int fork_nb)
{
	philo->forks--;
	pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
}

void	philo_eats(t_philo *philo)
{
	long	time;

	time = get_time(philo);
	philo->food_deadline = time + philo->hunger;
	printf("%li %i is eating\n", time, philo->number);
	while (1)
	{
		time = get_time(philo);
		if (time >= philo->life_deadline)
		{
			philo_dies(philo);
			break ;
		}
		else if (time >= philo->food_deadline)
		{
			philo->life_deadline = time + philo->hp;
			if (philo->number == philo->max_number)
				philo_puts_fork(philo, 0);
			else
				philo_puts_fork(philo, philo->number);
			philo_puts_fork(philo, philo->number - 1);
			philo_sleeps(philo);
			break ;
		}
	}
}

void	philo_sleeps(t_philo *philo)
{
	long		time;

	time = get_time(philo);
	printf("%li %i is sleeping\n", time, philo->number);
	philo->sleep_deadline = time + philo->sleepiness;
	while (1)
	{
		time = get_time(philo);
		if (time >= philo->life_deadline)
		{
			philo_dies(philo);
			break ;
		}
		else if (time >= philo->sleep_deadline)
		{
			break ;
			philo_takes_fork(philo, philo->number - 1);
			philo_takes_fork(philo, philo->number);
			break ;
		}
	}
}

void	philo_dies(t_philo *philo)
{
	philo->alive = 0;
	printf("MATARAM-ME! (%i)\n", philo->number);
}
