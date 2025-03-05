/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:59:06 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/05 23:30:19 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static int	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	if (should_stop(philo))
		return (0);
	pthread_mutex_lock(fork);
	if (should_stop(philo))
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	print_with_lock(philo, "has taken a fork");
	return (1);
}

static int	pick_up_forks(t_philo *philo)
{
	if (philo->number % 2 == 0)
	{
		if (!take_fork(philo->left_fork, philo))
			return (0);
		if (!take_fork(philo->right_fork, philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
	}
	else
	{
		if (!take_fork(philo->right_fork, philo))
			return (0);
		if (!take_fork(philo->left_fork, philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
	}
	return (1);
}

int	eat(t_philo *philo)
{
	long	eating_start;

	if (philo->number % 2 == 0)
		accurate_sleep(1);
	if (should_stop(philo))
		return (0);
	if (!pick_up_forks(philo))
		return (0);
	eating_start = get_timestamp_ms();
	// Update last eat time IMMEDIATELY after getting forks
	pthread_mutex_lock(&philo->last_eat_mutex);
	gettimeofday(&philo->last_eat, NULL);
	pthread_mutex_unlock(&philo->last_eat_mutex);
	print_with_lock(philo, "is eating");
	while (!should_stop(philo) && (get_timestamp_ms()
			- eating_start < philo->input[TIME_TO_EAT]))
		usleep(1000);
	release_forks(philo);
	if (!should_stop(philo))
	{
		pthread_mutex_lock(&philo->meal_mutex);
		philo->meal_count++;
		pthread_mutex_unlock(&philo->meal_mutex);
	}
	return (!should_stop(philo));
}
