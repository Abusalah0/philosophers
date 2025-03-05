/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:31:53 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/05 20:56:18 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void accurate_sleep(long ms)
{
    long start_time = get_timestamp_ms();
    long end_time = start_time + ms;
    
    while (get_timestamp_ms() < end_time)
        usleep(500); // Sleep in small increments to not oversleep
}

void sleep_philo(t_philo *philo, int time)
{
    // Only print and sleep if not stopped
    if (!should_stop(philo))
    {
        print_with_lock(philo, "is sleeping");
        
        // Use small sleep intervals and check stop flag between them
        int elapsed = 0;
        while (elapsed < time && !should_stop(philo))
        {
            int sleep_time = (time - elapsed < 10) ? (time - elapsed) : 10;
            usleep(sleep_time * 1000);
            elapsed += sleep_time;
        }
    }
}