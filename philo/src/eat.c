/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:36:50 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/01 17:08:07 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void release_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_lock(philo->print);
    printf("%d %d has released both forks\n", get_time(philo->start), philo->number);
    pthread_mutex_unlock(philo->print);
}

static void fork_sync(pthread_mutex_t *fork, t_philo *philo)
{
    pthread_mutex_lock(fork);
    pthread_mutex_lock(philo->print);
    printf("%d %d has taken a fork\n", get_time(philo->start), philo->number);
    pthread_mutex_unlock(philo->print);
}

void pick_up_forks(t_philo *philo)
{
    if (philo->number % 2 == 0)
    {
        fork_sync(philo->left_fork, philo);
        fork_sync(philo->right_fork, philo);
    }
    else
    {
        fork_sync(philo->right_fork, philo);
        fork_sync(philo->left_fork, philo);
    }
}

void eat(t_philo *philo)
{
    if (philo->number % 2 == 0)
        usleep(1000);
    pick_up_forks(philo);
    gettimeofday(&philo->last_eat, NULL);
    pthread_mutex_lock(philo->print);
    printf("%d %d is eating\n", get_time(philo->start), philo->number);
    pthread_mutex_unlock(philo->print);
    usleep(philo->input[TIME_TO_EAT] * 1000);
    release_forks(philo);
    pthread_mutex_lock(&philo->full);
    philo->num_of_eat++;
    pthread_mutex_unlock(&philo->full);
}
