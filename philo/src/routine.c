/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:26:02 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/08 13:16:05 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_full(t_philo *philo)
{
	bool	full;

	if (philo->input[NUM_TO_EAT] == -1)
	{
		return (false);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	full = philo->meal_count >= philo->input[NUM_TO_EAT];
	pthread_mutex_unlock(&philo->meal_mutex);
	return (full);
}

int	judgement_day(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(philo->stop_mutex);
	stop = *(philo->stop);
	pthread_mutex_unlock(philo->stop_mutex);
	return (stop);
}

void	think(t_philo *philo)
{
	if (!judgement_day(philo))
		print_with_safety(philo, "is thinking");
}

void	*lonely_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	print_with_safety(philo, "has taken a fork");
	sleep_and_check(philo->input[TIME_TO_DIE] + 10);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!judgement_day(philo))
	{
		if (check_full(philo))
		{
			break ;
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		if (!eat(philo))
		{
			break ;
		}
		if (check_full(philo))
		{
			break ;
		}
		sleep_philo(philo, philo->input[TIME_TO_SLEEP]);
		pthread_mutex_unlock(&philo->meal_mutex);
		think(philo);
	}
	return (NULL);
}
