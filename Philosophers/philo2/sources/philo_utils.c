/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 08:41:27 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/02/29 08:41:33 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	better_usleep(t_philo *philo, long deadline)
{
	while (get_time(philo) < deadline)
		usleep(500);
}

long	get_time(t_philo *philo)
{
	gettimeofday((struct timeval *)philo->watch, NULL);
	return (((philo->watch->sec * 1000000 + \
	philo->watch->mil_sec) - philo->birth_time) / 1000);
}

int	send_msg(t_philo *philo, char *msg, long time)
{
	if (philo->table->exit || philo->exit)
		return (0);
	printf("%li %i %s\n", time, philo->number, msg);
	return (1);
}

void	philo_takes_fork(t_philo *philo, int fork_nb, int hand)
{
	while (1)
	{
		pthread_mutex_lock(&philo->table->fork[fork_nb].mutex);
		if (!philo->table->fork[fork_nb].taken)
		{
			philo->table->fork[fork_nb].taken = 1;
			philo->fork[hand] = 1;
			pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
			pthread_mutex_lock(&philo->table->mutex);
			send_msg(philo, "has taken a fork", get_time(philo));
			pthread_mutex_unlock(&philo->table->mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
		usleep(500);
	}
}

void	philo_leaves_fork(t_philo *philo, int fork_nb, int hand)
{
	pthread_mutex_lock(&philo->table->fork[fork_nb].mutex);
	philo->fork[hand] = 0;
	philo->table->fork[fork_nb].taken = 0;
	pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
}
