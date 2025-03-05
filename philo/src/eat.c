/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:59:06 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/05 20:59:37 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void release_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
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
    // Even philosophers take left fork first, odd take right first
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
    // Small offset to prevent deadlocks for even philosophers
    if (philo->number % 2 == 0)
        accurate_sleep(1);
        
    if (should_stop(philo))
        return (0);
        
    if (!pick_up_forks(philo))
        return (0);
    
    // Mark eating start time
    long eating_start = get_timestamp_ms();
    
    // Update last eat time IMMEDIATELY after getting forks
    pthread_mutex_lock(&philo->last_eat_mutex);
    gettimeofday(&philo->last_eat, NULL);
    pthread_mutex_unlock(&philo->last_eat_mutex);
    
    print_with_lock(philo, "is eating");
    
    // Hold forks and eat for time_to_eat milliseconds
    // Use should_stop checks to exit earlier if needed
    while (!should_stop(philo) && (get_timestamp_ms() - eating_start < philo->input[TIME_TO_EAT]))
        usleep(1000); // Small sleep to reduce CPU usage
    
    release_forks(philo);
    
    // Update meal count if fully completed eating
    if (!should_stop(philo))
    {
        pthread_mutex_lock(&philo->meal_mutex);
        philo->meal_count++;
        pthread_mutex_unlock(&philo->meal_mutex);
    }
    
    return (!should_stop(philo));
}