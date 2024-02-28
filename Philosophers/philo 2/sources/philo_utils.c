#include "philo.h"

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

void	philo_tries_to_eat(t_philo *philo)
{
	if (philo->number % 2 != 0)
	{
		if (philo->number != 1)
			philo_takes_fork(philo, philo->number - 2, 0);
		else
			philo_takes_fork(philo, philo->max_number - 1, 0);
		philo_takes_fork(philo, philo->number - 1, 1);
	}
	else
	{
		philo_takes_fork(philo, philo->number - 1, 1);
		philo_takes_fork(philo, philo->number - 2, 0);
	}
}

void	philo_takes_fork(t_philo *philo, int fork_nb, int hand)
{
	while (1)
	{
		pthread_mutex_lock(&philo->table->mutex);
		pthread_mutex_lock(&philo->table->fork[fork_nb].mutex);
		if (philo->table->exit)
			return ;
		if (!philo->table->fork[fork_nb].taken)
		{
			philo->table->fork[fork_nb].taken = 1;
			philo->fork[hand] = 1;
			send_msg(philo, "has taken a fork", get_time(philo));
			pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
			pthread_mutex_unlock(&philo->table->mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
		pthread_mutex_unlock(&philo->table->mutex);
		usleep(1000);
	}
}

void	philo_puts_fork(t_philo *philo, int fork_nb, int hand)
{
	pthread_mutex_lock(&philo->table->fork[fork_nb].mutex);
	philo->fork[hand] = 0;
	philo->table->fork[fork_nb].taken = 0;
	pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
}