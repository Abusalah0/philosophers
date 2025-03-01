/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 03:06:18 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/01 16:59:36 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_prog(t_prog *prog)
{
    int i;

    i = -1;
    while (++i < prog->input[NUM_OF_PHILO])
    {
        pthread_mutex_destroy(&prog->philos[i].full);
    }
    free(prog->forks);
    free(prog->philos);
    free(prog->input);
    free(prog);
}

