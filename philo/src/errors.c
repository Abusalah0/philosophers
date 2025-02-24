/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 03:06:18 by abdsalah          #+#    #+#             */
/*   Updated: 2025/02/24 03:47:56 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    free_prog(t_prog *prog)
{
    if (!prog)
        return ;
    if (prog->philos)
    {
        free(prog->philos);
        prog->philos = NULL;
    }
    if (prog->forks)
    {
        free(prog->forks);
        prog->forks = NULL;
    }
    if (prog->input)
    {
        free(prog->input);
        prog->input = NULL;
    }
}
