/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:08:56 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/01 17:02:17 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void sleep_philo(t_philo *philo, int time)
{
    pthread_mutex_lock(philo->print);
    printf("%d %d is sleeping\n", get_time(philo->start), philo->number);
    pthread_mutex_unlock(philo->print);
    usleep(time * 1000);
}

void *routine(void *ptr)
{
    t_philo *philo = (t_philo *)ptr;
    
    while (1)
    {
        if (philo->input[NUM_TO_EAT] != -1 && philo->num_of_eat >= philo->input[NUM_TO_EAT])
            break;
        
        pthread_mutex_lock(philo->print);
        printf("%d %d is thinking\n", get_time(philo->start), philo->number);
        pthread_mutex_unlock(philo->print);
        
        eat(philo);
        sleep_philo(philo, philo->input[TIME_TO_SLEEP]);
    }
    return (NULL);
}

