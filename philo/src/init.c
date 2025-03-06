/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:09:15 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/06 21:54:15 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	assign_philos(t_prog *prog, struct timeval start, int i, int *input)
{
	if (pthread_mutex_init(&prog->philos[i].meal_mutex, NULL) != 0
		|| pthread_mutex_init(&prog->philos[i].last_eat_mutex, NULL) != 0)
	{
		while (--i >= 0)
		{
			pthread_mutex_destroy(&prog->philos[i].meal_mutex);
			pthread_mutex_destroy(&prog->philos[i].last_eat_mutex);
		}
		return (0);
	}
	prog->philos[i].input = input;
	prog->philos[i].number = i + 1;
	prog->philos[i].meal_count = 0;
	prog->philos[i].left_fork = &prog->forks[i];
	prog->philos[i].right_fork = &prog->forks[(i + 1)
		% prog->input[NUM_OF_PHILO]];
	prog->philos[i].start = start;
	prog->philos[i].print = &prog->print;
	prog->philos[i].last_eat = start;
	prog->philos[i].stop_mutex = &prog->stop_mutex;
	prog->philos[i].stop = &prog->stop;
	return (1);
}

static int	init_mutexes(t_prog *prog)
{
	if (pthread_mutex_init(&prog->print, NULL) != 0)
	{
		return (0);
	}
	if (pthread_mutex_init(&prog->stop_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&prog->print);
		return (0);
	}
	return (1);
}

static int	init_philos(t_prog *prog)
{
	int				i;
	struct timeval	start;

	gettimeofday(&start, NULL);
	prog->start_time = start;
	prog->philos = malloc(sizeof(t_philo) * prog->input[NUM_OF_PHILO]);
	if (!prog->philos)
		return (0);
	i = -1;
	while (++i < prog->input[NUM_OF_PHILO])
	{
		if (!assign_philos(prog, start, i, prog->input))
		{
			free_prog(prog, 1, 1, 1);
			return (0);
		}
	}
	return (1);
}

static int	init_forks(t_prog *prog)
{
	int	i;

	prog->forks = malloc(sizeof(pthread_mutex_t) * prog->input[NUM_OF_PHILO]);
	if (!prog->forks)
		return (0);
	i = -1;
	while (++i < prog->input[NUM_OF_PHILO])
	{
		if (pthread_mutex_init(&prog->forks[i], NULL) != 0)
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&prog->forks[i]);
			}
			free(prog->forks);
			return (0);
		}
	}
	return (1);
}

int	init(t_prog *prog, int argc, char **argv)
{
	int	*input;

	input = check_args(argc, argv);
	if (!input)
		return (0);
	prog->input = input;
	prog->stop = 0;
	if (!init_mutexes(prog))
	{
		free(input);
		input = NULL;
		return (0);
	}
	if (!init_forks(prog))
	{
		pthread_mutex_destroy(&prog->print);
		pthread_mutex_destroy(&prog->stop_mutex);
		free(input);
		input = NULL;
		return (0);
	}
	if (!init_philos(prog))
		return (0);
	return (1);
}
