/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:26:02 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/06 18:33:52 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(philo->stop_mutex);
	stop = *(philo->stop);
	pthread_mutex_unlock(philo->stop_mutex);
	return (stop);
}

void	think(t_philo *philo)
{
	if (!should_stop(philo))
		print_with_safety(philo, "is thinking");
}

void	*lonely_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	print_with_safety(philo, "has taken a fork");
	accurate_sleep(philo->input[TIME_TO_DIE] + 10);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!should_stop(philo))
	{
		pthread_mutex_lock(&philo->meal_mutex);
		if (philo->input[NUM_TO_EAT] != -1
			&& philo->meal_count >= philo->input[NUM_TO_EAT])
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		if (!eat(philo))
			break ;
		sleep_philo(philo, philo->input[TIME_TO_SLEEP]);
		think(philo);
	}
	return (NULL);
}
