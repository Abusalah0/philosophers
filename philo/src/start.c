/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:38:14 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/05 16:24:04 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Special routine for the case of only one philosopher */
void *one_philo_routine(void *ptr)
{
    t_philo *philo = (t_philo *)ptr;
    
    // Take the only available fork
    pthread_mutex_lock(philo->left_fork);
    print_with_lock(philo, "has taken a fork");
    
    // With only one fork, philosopher can't eat and will eventually die
    // Wait until time_to_die passes
    accurate_sleep(philo->input[TIME_TO_DIE] + 10);
    
    // Release the fork before exiting (just for cleanup)
    pthread_mutex_unlock(philo->left_fork);
    
    return (NULL);
}

int create_philos(t_prog *prog)
{
    int i;

    // Special case: only one philosopher
    if (prog->input[NUM_OF_PHILO] == 1)
    {
        // Create thread with special one-philosopher routine
        if (pthread_create(&prog->philos[0].id, NULL, one_philo_routine, &prog->philos[0]))
            return (0);
            
        // No need to wait for philosopher to die, monitor will handle that
        return (1);
    }

    // Create all philosopher threads for normal case
    i = 0;
    while (i < prog->input[NUM_OF_PHILO])
    {
        if (pthread_create(&prog->philos[i].id, NULL, routine, &prog->philos[i]))
            return (0);
        i++;
    }
    
    return (1);
}

int join_philos(t_prog *prog)
{
    int i;
    
    i = 0;
    while (i < prog->input[NUM_OF_PHILO])
    {
        if (pthread_join(prog->philos[i].id, NULL))
            return (0);
        i++;
    }
    return (1);
}

int start(t_prog *prog)
{
    pthread_t monitor_thread;
    
    if (!create_philos(prog))
        return (0);
        
    // Create monitor thread after philosophers start
    if (pthread_create(&monitor_thread, NULL, monitor, prog))
        return (0);
        
    // Wait for monitor to finish
    pthread_join(monitor_thread, NULL);
    
    // Set stop flag for all philosophers
    pthread_mutex_lock(&prog->stop_mutex);
    prog->stop = 1;
    pthread_mutex_unlock(&prog->stop_mutex);
    
    // Wait for all philosophers to finish
    join_philos(prog);
    
    return (1);
}