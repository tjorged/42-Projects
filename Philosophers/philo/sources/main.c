/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:17:14 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/02/07 14:17:16 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutexes_handler(t_table *table, char mode)
{
	int	i;

	i = -1;
	if (mode == 'c')
	{
		while (++i < table->p_nb)
			pthread_mutex_init(&table->fork[i].mutex, NULL);
		
	}
	else if (mode == 'd')
	{
		while (++i < table->p_nb)
			pthread_mutex_destroy(&table->fork[i].mutex);
	}
	return ;
}

int	end_program(t_table *table)
{
	free(table->philo);
	free(table->fork);
	mutexes_handler(table, 'd');
	return (0);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->table->start);
	if (philo->table->error)
		return (0);
	first_dinner(philo);
	return (NULL);
}

int	threads_creator(t_table *table)
{
	char	*error_msg;
	int		i;

	error_msg = "Error: Something went wrong while creating a thread\n";
	i= -1;
	table->start = 0;
	while (++i < table->p_nb)
	{
		if (pthread_create(&table->philo[i].soul, NULL, \
		&philo_life, &table->philo[i]) != 0)
		{
			write(2 , error_msg, 53);
			table->error = 1;
			return (0);
		}
	}
	table->start = 1;
	return (1);
}

int	threads_joiner(t_table *table, int limiter)
{
	int		i;
	char	*error_msg;

	error_msg = "Error: Something went wrong while joining a thread\n";
	i= -1;
	while (++i < limiter)
	{
		if (pthread_join(table->philo[i].soul, NULL) != 0)
		{
			write(2 , error_msg, 52);
			table->error = 1;
			return (0);
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	static t_table	table;

	if (!parser(&table, argc, argv))
		return (0);
	mutexes_handler(&table, 'c');
	if (!threads_creator(&table))
		return (end_program(&table));
	if (!threads_joiner(&table, table.p_nb))
		return (end_program(&table));
	return (end_program(&table));
}
