/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:08:56 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/01 15:04:15 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(t_philo *philo)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    pthread_mutex_lock(philo->print);
    printf("Hello from routine\n");
    printf("%d time %ld.%06ld\n", philo->number, tv.tv_sec, tv.tv_usec);
    pthread_mutex_unlock(philo->print);
    return (NULL);
}
