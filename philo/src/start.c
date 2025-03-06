/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:38:14 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/06 18:14:05 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lonely_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(philo->left_fork);
	print_with_safety(philo, "has taken a fork");
	accurate_sleep(philo->input[TIME_TO_DIE] + 10);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

int	create_philos(t_prog *prog)
{
	int	i;

	if (prog->input[NUM_OF_PHILO] == 1)
	{
		if (pthread_create(&prog->philos[0].id, NULL, lonely_routine,
				&prog->philos[0]))
			return (0);
		return (1);
	}
	i = 0;
	while (i < prog->input[NUM_OF_PHILO])
	{
		if (pthread_create(&prog->philos[i].id, NULL, routine,
				&prog->philos[i]))
			return (0);
		i++;
	}
	return (1);
}

int	join_philos(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->input[NUM_OF_PHILO])
	{
		if (pthread_join(prog->philos[i].id, NULL))
			return (0);
		i++;
	}
	return (1);
}

int	start(t_prog *prog)
{
	pthread_t	monitor_thread;

	if (!create_philos(prog))
		return (0);
	if (pthread_create(&monitor_thread, NULL, monitor, prog))
		return (0);
	if (pthread_join(monitor_thread, NULL))
		return (0);
	pthread_mutex_lock(&prog->stop_mutex);
	prog->stop = 1;
	pthread_mutex_unlock(&prog->stop_mutex);
	if (!join_philos(prog))
		return (0);
	return (1);
}
