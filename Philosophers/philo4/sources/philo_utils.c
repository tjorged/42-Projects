#include "philo.h"

long	get_time(t_philo *philo)
{
	gettimeofday((struct timeval *)philo->watch, NULL);
	return (((philo->watch->sec * 1000000 + philo->watch->mil_sec) - philo->birth_time) / 1000);
}

int	send_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->table->end)
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return (0);
	}
	printf("%li %i %s\n", get_time(philo), philo->number, msg);
	pthread_mutex_unlock(&philo->table->mutex);
	return (1);
}

void	philo_tries_to_eat(t_philo *philo)
{
	if (philo->number % 2 != 0)
	{
		philo_takes_fork(philo, philo->number - 1, 'l');
		if (philo->number == philo->max_number && philo->max_number != 1)
			philo_takes_fork(philo, 0, 'r');
		else if (philo->max_number != 1)
			philo_takes_fork(philo, philo->number, 'r');
	}
	else if (philo->number % 2 == 0)
	{
		if (philo->number == philo->max_number && philo->max_number != 1)
			philo_takes_fork(philo, 0, 'r');
		else if (philo->max_number != 1)
			philo_takes_fork(philo, philo->number, 'r');
		philo_takes_fork(philo, philo->number - 1, 'l');
	}
}

void	philo_takes_fork(t_philo *philo, int fork_nb, char hand)
{
	while (1)
	{
		pthread_mutex_lock(&philo->table->fork[fork_nb].mutex);
		if (!philo->table->fork[fork_nb].taken)
		{
			philo->table->fork[fork_nb].taken = 1;
			if (hand == 'l')
				philo->lfork = 1;
			else if (hand == 'r')
				philo->rfork = 1;
			pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
			send_msg(philo, "has taken a fork");
			break ;
		}
		pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
	}
}

void	philo_puts_fork(t_philo *philo, int fork_nb, char hand)
{
	pthread_mutex_lock(&philo->table->fork[fork_nb].mutex);
	if (hand == 'l')
		philo->lfork = 0;
	else if (hand == 'r')
		philo->rfork = 0;
	philo->table->fork[fork_nb].taken = 0;
	pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
}