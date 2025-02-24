/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:07:42 by abdsalah          #+#    #+#             */
/*   Updated: 2025/02/24 08:07:45 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int join_philos(t_prog *prog)
{
    int i;

    i = 0;
    while (i < prog->input[NUM_OF_PHILO])
    {
        if (pthread_join(prog->philos[i].id, NULL))
        {
            while (i >= 0)
            {
                pthread_detach(prog->philos[i].id);
                i--;
            }
            return (0);
        }
    }
    return (1);
}

static int create_philos(t_prog *prog)
{
    int i;

    i = 0;
    while (i < prog->input[NUM_OF_PHILO])
    {
        if (pthread_create(&prog->philos[i].id, NULL, routine, &prog->philos[i]))
        {
            while (i >= 0)
            {
                pthread_detach(prog->philos[i].id);
                i--;
            }
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
    if (!join_philos(prog))
        return (0);
    return (1);
}
