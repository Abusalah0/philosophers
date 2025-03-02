/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:07:42 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/01 15:07:51 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int create_philos(t_prog *prog)
{
    int i;

    i = 0;
    while (i < prog->input[NUM_OF_PHILO])
    {
        if (pthread_create(&prog->philos[i].id, NULL, routine, &prog->philos[i]))
        {
            return (0);
        }
        i++;
    }
    i = 0;
    while (i < prog->input[NUM_OF_PHILO])
    {
        if (pthread_join(prog->philos[i].id, NULL))
        {
            return (0);
        }
        i++;
    }
    return (1);
}

int start(t_prog *prog)
{
    if (!create_philos(prog))
        return (0);
    return (1);
}
