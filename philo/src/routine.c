/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:08:56 by abdsalah          #+#    #+#             */
/*   Updated: 2025/02/24 16:14:50 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void *routine(t_philo *philo)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    pthread_mutex_lock(philo->print);
    printf("Hello from routine\n");
    printf("%d time %ld.%06ld\n", philo->number, tv.tv_sec, tv.tv_usec);
    pthread_mutex_unlock(philo->print);
    pthread_detach(philo->id);
    return (NULL);
}
