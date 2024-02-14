#include "philo.h"

void	philo_thinks(t_philo *philo)
{
	printf("%i is thinking\n", philo->number);
}

void	philo_takes_fork(t_philo *philo, int fork_nb)
{
	pthread_mutex_lock(&philo->table->fork[fork_nb].mutex);
	philo->forks++;
	printf("%i has taken a fork\n", philo->number);
}

void 	first_dinner(t_philo *philo)
{
	if	(philo->number % 2 != 0)
	{
		philo_takes_fork(philo, philo->number - 1);
		philo_takes_fork(philo, philo->number);
	}
	else
		philo_thinks(philo);
}

// void	philo_puts_fork(t_philo *philo)
// {
// 	philo->forks--;
// 	if (philo->number == philo->table->p_nb)
// 		philo->table->philo[0].forks++;
// 	else
// 		philo->table->philo[philo->number + 1].forks++;
// }

// void	philo_eats()
// {

// }

// void	philo_sleeps()
// {

// }

// void	philo_dies()
// {

// }