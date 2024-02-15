/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:17:03 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/02/07 14:17:07 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	int				n;
	int				v;

	i = 0;
	n = 0;
	v = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			v = -v;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = (n * 10) + (nptr[i] - 48);
		i++;
	}
	return (n * v);
}

static int	arguments_validator(int argc, char **argv)
{
	int	i;
	int	j;

	j = 0;
	while (++j < argc)
	{
		i = 0;
		while (argv[j][i] == ' ')
			i++;
		if (argv[j][i] == '+')
			i++;
		while (argv[j][i] >= '0' && argv[j][i] <= '9')
			i++;
		while (argv[j][i] == ' ')
			i++;
		if (argv[j][i] != '\0')
		{
			write (2, "Error: Invalid arguments\n", 26);
			return (0);
		}
	}
	return (1);
}

static int	value_initializer(t_table *table, int i)
{
	table->philo[i].number = i + 1;
	table->philo[i].max_number = table->p_nb;
	table->philo[i].hp = table->tt_die;
	table->philo[i].alive = 1;
	table->philo[i].hunger = table->tt_eat;
	table->philo[i].eating = 0;
	table->philo[i].meals_left = table->eating_times;
	table->philo[i].forks = 0;
	table->philo[i].sleepiness = table->tt_sleep;
	table->philo[i].sleeping = 0;
	table->philo[i].thinking = 0;
	table->philo[i].table = table;
	table->philo[i].watch = malloc(sizeof(t_timeval));
	if (!table->philo[i].watch)
		return (end_program(table, i), 0);
	return (1);
}

static int	conception(t_table *table)
{
	int	i;

	table->philo = malloc(sizeof(t_philo) * table->p_nb);
	if (!table->philo)
		return (0);
	table->fork = malloc(sizeof(t_fork) * table->p_nb);
	if (!table->fork)
		return (free (table->philo), 0);
	table->clock = malloc(sizeof(t_timeval));
	if (!table->clock)
		return (free(table->philo), free(table->fork), 0);
	i = -1;
	while (++i < table->p_nb)
	{
		if (!value_initializer(table, i))
			return (0);
	}
	return (1);
}

int	parser(t_table *table, int argc, char **argv)
{
	if (argc < 5)
		write(2, "Error: Not enough arguments\n", 29);
	else if (argc > 6)
		write(2, "Error: Too many arguments\n", 27);
	if ((argc < 5 || argc > 6) || !arguments_validator(argc, argv))
		return (0);
	table->p_nb = ft_atoi(argv[1]);
	table->tt_die = ft_atoi(argv[2]);
	table->tt_eat = ft_atoi(argv[3]);
	table->tt_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->eating_times = ft_atoi(argv[5]);
	else
		table->eating_times = -1;
	if (!conception(table))
		return (write(2, "Error: failed to allocate memory\n", 34), 0);
	return (1);
}
