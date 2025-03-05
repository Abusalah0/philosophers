/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:25:37 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/05 16:38:36 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_full(t_prog *prog)
{
    int i = 0;
    int all_full = 1;
    
    if (prog->input[NUM_TO_EAT] == -1)
        return (0);
        
    while (i < prog->input[NUM_OF_PHILO])
    {
        pthread_mutex_lock(&prog->philos[i].meal_mutex);
        if (prog->philos[i].meal_count < prog->input[NUM_TO_EAT])
        {
            all_full = 0;
            pthread_mutex_unlock(&prog->philos[i].meal_mutex);
            break;
        }
        pthread_mutex_unlock(&prog->philos[i].meal_mutex);
        i++;
    }
    return (all_full);
}

int check_death(t_prog *prog)
{
    int i = 0;
    long time_since_last_eat;
    struct timeval current_time;
    struct timeval last_eat_time;
    
    gettimeofday(&current_time, NULL);
    
    while (i < prog->input[NUM_OF_PHILO])
    {
        // First check if simulation already stopped
        pthread_mutex_lock(&prog->stop_mutex);
        if (prog->stop)
        {
            pthread_mutex_unlock(&prog->stop_mutex);
            return (1);
        }
        pthread_mutex_unlock(&prog->stop_mutex);

        // Check philosopher's last meal time
        pthread_mutex_lock(&prog->philos[i].last_eat_mutex);
        last_eat_time = prog->philos[i].last_eat;
        pthread_mutex_unlock(&prog->philos[i].last_eat_mutex);
        
        time_since_last_eat = diff(last_eat_time, current_time);
        
        if (time_since_last_eat > prog->input[TIME_TO_DIE])
        {
            // Lock print mutex AND stop mutex together
            pthread_mutex_lock(&prog->stop_mutex);
            pthread_mutex_lock(&prog->print);
            
            // Only print death message if stop is still 0
            if (!prog->stop)
            {
                prog->stop = 1;  // Set stop flag first
                printf("%d %d died\n", get_time(prog->philos[i].start), 
                       prog->philos[i].number);
                pthread_mutex_unlock(&prog->print);
                pthread_mutex_unlock(&prog->stop_mutex);
                return (1);
            }
            
            pthread_mutex_unlock(&prog->print);
            pthread_mutex_unlock(&prog->stop_mutex);
            return (1);
        }
        i++;
    }
    return (0);
}

void *monitor(void *ptr)
{
    t_prog *prog = (t_prog *)ptr;
    int stop_flag = 0;
    
    // Allow philosophers time to start
    accurate_sleep(1);
    while (!stop_flag)
    {
        // Check for death first
        if (check_death(prog))
            break;
        // Only then check if all philosophers are full
        if (prog->input[NUM_TO_EAT] != -1 && check_full(prog))
        {
            pthread_mutex_lock(&prog->stop_mutex);
            pthread_mutex_lock(&prog->print);
            if (!prog->stop) // Only print if we haven't stopped yet
            {
                prog->stop = 1;
                printf("All philosophers have eaten enough times\n");
            }
            pthread_mutex_unlock(&prog->print);
            pthread_mutex_unlock(&prog->stop_mutex);
            break;
        }
        // Check stop flag
        pthread_mutex_lock(&prog->stop_mutex);
        stop_flag = prog->stop;
        pthread_mutex_unlock(&prog->stop_mutex);
        usleep(500);
    }
    return (NULL);
}
