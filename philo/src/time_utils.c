/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:32:16 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/05 16:33:26 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"  

int get_time(struct timeval start)
{
    struct timeval now;

    gettimeofday(&now, NULL);
    if (start.tv_sec == 0 && start.tv_usec == 0)
        return ((now.tv_sec * 1000 + now.tv_usec / 1000));
    return ((now.tv_sec * 1000 + now.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000));
}

long diff(struct timeval start, struct timeval end)
{
    return ((end.tv_sec - start.tv_sec) * 1000 + 
            (end.tv_usec - start.tv_usec) / 1000);
}