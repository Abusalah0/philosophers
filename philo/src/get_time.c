/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:19:21 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/01 17:12:27 by abdsalah         ###   ########.fr       */
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