#include "philo.h"

long	get_time(t_philo *philo)
{
	gettimeofday((struct timeval *)philo->watch, NULL);
	return ((philo->watch->sec * 1000000 + \
		philo->watch->mil_sec) / 1000 - philo->birth_time);
}

int	dead_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->table->philo_died)
	{
		pthread_mutex_lock(&philo->mutex);
		philo->exit = 1;
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(&philo->table->mutex);
		return (1);
	}
	return (0);
}

void	philo_tries_to_eat(t_philo *philo)
{
	
	if (dead_philo(philo))
		return ;
	pthread_mutex_unlock(&philo->table->mutex);
	printf("TENTEI!\n");
	if (philo->number % 2 != 0)
	{
		if (philo->number == philo->max_number && philo->max_number != 1)
			philo_takes_fork(philo, 0, 'r');
		else if (philo->max_number != 1)
			philo_takes_fork(philo, philo->number, 'r');
		else
			printf("Nao entrei em nenhuma\n");
		printf("O!\n");
		philo_takes_fork(philo, philo->number - 1, 'l');
	}
	if (philo->number % 2 == 0)
	{
		philo_takes_fork(philo, philo->number - 1, 'l');
		if (philo->number == philo->max_number && philo->max_number != 1)
			philo_takes_fork(philo, 0, 'r');
		else if (philo->max_number != 1)
			philo_takes_fork(philo, philo->number, 'r');
	}
}

void	philo_takes_fork(t_philo *philo, int fork_nb, char hand)
{
	printf("entrei uma vez\n");
	pthread_mutex_lock(&philo->mutex);
	if (hand == 'l')
	{
		printf("espera esquerda\n");
		philo->waiting_lfork = 1;
	}
	if (hand == 'r')
	{
		printf("espera direita\n");
		philo->waiting_rfork = 1;
	}
	philo->wating_starvation = philo->life_deadline; 
	pthread_mutex_unlock(&philo->mutex);
	//printf("fork_nb = %p\n", &philo->table->fork[fork_nb].mutex);
	pthread_mutex_lock(&philo->table->fork[fork_nb].mutex);
	if (dead_philo(philo))
	{
		printf("alguem ta morto\n");
//		pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
		return ;
	}
	printf("%li %i has taken a fork\n", get_time(philo), philo->number);
	pthread_mutex_lock(&philo->mutex);
	if (hand == 'l')
	{
		printf("TAKES LEFT\n");
		philo->lfork = 1;
	}
	if (hand == 'r')
	{
		printf("TAKES RIGHT\n");
		philo->rfork = 1;
	}
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->table->mutex);
}

void	philo_puts_fork(t_philo *philo, int fork_nb, char hand)
{
	pthread_mutex_lock(&philo->mutex);
	if (hand == 'l')
	{
		printf("PUTS LEFT\n");
		philo->lfork = 0;
	}
	if (hand == 'r')
	{
		printf("PUTS RIGHT\n");
		philo->rfork = 0;
	}
	pthread_mutex_unlock(&philo->mutex);
	printf("fork_nb = %p\n", &philo->table->fork[fork_nb].mutex);
	if(pthread_mutex_trylock(&philo->table->fork[fork_nb].mutex) == 0)
		printf("nao estava locked\n");
	else
		printf("estava locked\n");
	pthread_mutex_unlock(&philo->table->fork[fork_nb].mutex);
}