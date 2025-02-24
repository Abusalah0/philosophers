/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:07:42 by abdsalah          #+#    #+#             */
/*   Updated: 2025/02/24 17:25:24 by ahramada         ###   ########.fr       */
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
