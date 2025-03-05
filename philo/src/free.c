/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:24:50 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/05 23:30:16 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutexes(t_prog *prog)
{
	pthread_mutex_destroy(&prog->print);
	pthread_mutex_destroy(&prog->stop_mutex);
}

void	free_forks(t_prog *prog)
{
	int	i;

	i = -1;
	while (++i < prog->input[NUM_OF_PHILO])
		pthread_mutex_destroy(&prog->forks[i]);
	free(prog->forks);
}

void	free_philos(t_prog *prog)
{
	int	i;

	i = -1;
	while (++i < prog->input[NUM_OF_PHILO])
	{
		pthread_mutex_destroy(&prog->philos[i].meal_mutex);
		pthread_mutex_destroy(&prog->philos[i].last_eat_mutex);
	}
	free(prog->philos);
}

void	free_prog(t_prog *prog, bool forks, bool philos, bool mutexes)
{
	if (!prog)
		return ;
	if (philos)
	{
		if (prog->philos)
			free_philos(prog);
	}
	if (forks)
	{
		if (prog->forks)
			free_forks(prog);
	}
	if (mutexes)
		free_mutexes(prog);
	if (prog->input)
		free(prog->input);
}
