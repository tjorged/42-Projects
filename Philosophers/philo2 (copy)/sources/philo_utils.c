#include "philo.h"

long long	get_time(t_philo *philo)
{
	gettimeofday((struct timeval *)philo->watch, NULL);
	return (((philo->watch->sec * 1000000 + \
	philo->watch->mil_sec) - philo->birth_time) / 1000);
}

void	kill_all_philos(t_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&philo->table->mutex);
	philo->exit = 1;
	while (++i < philo->table->p_nb)
	{
		if (i == philo->number - 1)
			i++;
		pthread_mutex_lock(&philo->table->philo[i].mutex);
		printf("Locked: %i\n", philo->table->philo[i].number);
		philo->table->philo[i].exit = 1;
	}
	i = -1;
	while (++i < philo->table->p_nb)
		pthread_mutex_unlock(&philo->table->philo[i].mutex);
	pthread_mutex_unlock(&philo->table->mutex);
}

int	send_msg(t_philo *philo, char *msg, long long time)
{
	if (philo->exit || !philo->meals_left)
		return (0);
	printf("%lli %i %s\n", time, philo->number, msg);
	return (1);
}

void	philo_dies(t_philo *philo, long long time)
{
	int	msg;

	pthread_mutex_lock(&philo->table->mutex);
	msg = send_msg(philo, "died", time);
	pthread_mutex_unlock(&philo->table->mutex);
	if (!msg)
	{
		pthread_mutex_unlock(&philo->mutex);
		return ;
	}
	kill_all_philos(philo);
}

int	im_dead(t_philo *philo, long long time)
{
	if (!time)
		time = get_time(philo);
	if (philo->exit || !philo->meals_left)
		return (1);
	else if (time >= philo->life_deadline)
	{
		philo_dies(philo, time);
		return (1);
	}
	return (0);
}

int	has_both_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	if (im_dead(philo, 0))
	{
		pthread_mutex_unlock(&philo->mutex);
		return (1);
	}
	else if (philo->lfork && philo->rfork)
	{
		pthread_mutex_unlock(&philo->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex);
	return (0);
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
	while (!has_both_forks(philo))
		;
}

void	philo_takes_fork(t_philo *philo, int fork_nb, char hand)
{
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		pthread_mutex_lock(&philo->table->fork[fork_nb].mutex);
		if (im_dead(philo, 0))
			break;
		if (!philo->table->fork[fork_nb].taken)
		{
			philo->table->fork[fork_nb].taken = 1;
			if (hand == 'l')
				philo->lfork = 1;
			else if (hand == 'r')
				philo->rfork = 1;
			pthread_mutex_lock(&philo->table->mutex);
			send_msg(philo, "has taken a fork", get_time(philo));
			pthread_mutex_unlock(&philo->table->mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
		pthread_mutex_unlock(&philo->mutex);
	}
	pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
	pthread_mutex_unlock(&philo->mutex);
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
