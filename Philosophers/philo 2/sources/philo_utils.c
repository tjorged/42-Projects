#include "philo.h"

long	get_time(t_philo *philo)
{
	gettimeofday((struct timeval *)philo->watch, NULL);
	return (((philo->watch->sec * 1000000 + \
	philo->watch->mil_sec) - philo->birth_time) / 1000);
}

void	kill_all_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->p_nb)
		table->philo[i].exit = 1;
}

int	send_msg(t_philo *philo, char *msg, long time)
{
	if (philo->exit)
		return (0);
	printf("%li %i %s\n", time, philo->number, msg);
	return (1);
}

void	philo_dies(t_philo *philo, long time)
{
	if (!send_msg(philo, "died", time))
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return ;
	}
	kill_all_philos(philo->table);
}

int	im_dead(t_philo *philo, long time)
{
	if (philo->exit)
		return (1);
	if (time >= philo->life_deadline)
	{
		philo_dies(philo, time);
		return (1);
	}
	return (0);
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
	long	time;

	while (1)
	{
		pthread_mutex_lock(&philo->table->mutex);
		pthread_mutex_lock(&philo->table->fork[fork_nb].mutex);
		time = get_time(philo);
		if (im_dead(philo, time))
			break	;
		if (!philo->table->fork[fork_nb].taken)
		{
			philo->table->fork[fork_nb].taken = 1;
			philo->fork[hand] = 1;
			send_msg(philo, "has taken a fork", time);
			break ;
		}
		pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
		pthread_mutex_unlock(&philo->table->mutex);
		usleep(3000);
	}
	pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
	pthread_mutex_unlock(&philo->table->mutex);
}

void	philo_puts_fork(t_philo *philo, int fork_nb, int hand)
{
	pthread_mutex_lock(&philo->table->fork[fork_nb].mutex);
	philo->fork[hand] = 0;
	philo->table->fork[fork_nb].taken = 0;
	pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
}