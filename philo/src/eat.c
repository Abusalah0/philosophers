/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:26:13 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/05 16:38:03 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void release_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    if (!should_stop(philo))
        print_with_lock(philo, "has released both forks");
}

static int take_fork(pthread_mutex_t *fork, t_philo *philo)
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

static int pick_up_forks(t_philo *philo)
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

int eat(t_philo *philo)
{
    struct timeval current_time;
    
    if (philo->number % 2 == 0)
        accurate_sleep(1);
    if (should_stop(philo))
        return (0);
    if (!pick_up_forks(philo))
        return (0);
    // Check again before printing eat status
    if (should_stop(philo))
    {
        release_forks(philo);
        return (0);
    }
    print_with_lock(philo, "is eating");
    // Update last eat time
    gettimeofday(&current_time, NULL);
    pthread_mutex_lock(&philo->last_eat_mutex);
    philo->last_eat = current_time;
    pthread_mutex_unlock(&philo->last_eat_mutex);
    // Sleep in small increments and check stop flag
    int elapsed = 0;
    while (elapsed < philo->input[TIME_TO_EAT] && !should_stop(philo))
    {
        int sleep_time = (philo->input[TIME_TO_EAT] - elapsed < 10) ? 
                         (philo->input[TIME_TO_EAT] - elapsed) : 10;
        usleep(sleep_time * 1000);
        elapsed += sleep_time;
    }
    release_forks(philo);
    // Update meal count
    if (!should_stop(philo))
    {
        pthread_mutex_lock(&philo->meal_mutex);
        philo->meal_count++;
        pthread_mutex_unlock(&philo->meal_mutex);
    }
    return (!should_stop(philo));
}
