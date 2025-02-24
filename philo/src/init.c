/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 03:19:23 by abdsalah          #+#    #+#             */
/*   Updated: 2025/02/24 08:11:53 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int init_print(t_prog *prog)
{
    prog->print = malloc(sizeof(pthread_mutex_t));
    if (!prog->print)
    {
        free(prog->input);
        free(prog);
        return (0);
    }
    if (pthread_mutex_init(prog->print, NULL))
    {
        free(prog->input);
        free(prog->print);
        free(prog);
        return (0);
    }
    return (1);
}

static int init_philos(t_prog *prog)
{
    int i;

    prog->philos = malloc(sizeof(t_philo) * prog->input[NUM_OF_PHILO]);
    if (!prog->philos)
    {
        free(prog->input);
        free(prog);
        return (0);
    }
    i = 0;
    while (i < prog->input[NUM_OF_PHILO])
    {
        prog->philos[i].number = i + 1;
        prog->philos[i].num_of_eat = 0;
        prog->philos[i].left_fork = &prog->forks[i];
        prog->philos[i].right_fork = &prog->forks[(i + 1) % prog->input[NUM_OF_PHILO]];
        gettimeofday(&prog->philos[i].start, NULL);
        gettimeofday(&prog->philos[i].last_eat, NULL);
        i++;    
    }
    return (1);    
}

static int init_forks(t_prog *prog)
{
    int i;

    i = -1;
    prog->forks = malloc(sizeof(pthread_mutex_t) * prog->input[NUM_OF_PHILO]);
    if (!prog->forks)
    {
        free(prog->input);
        free(prog->philos);
        free(prog);
        return (0);
    }
    while (++i < prog->input[NUM_OF_PHILO])
    {
        if (pthread_mutex_init(&prog->forks[i], NULL))
        {
            while (--i >= 0)
                pthread_mutex_destroy(&prog->forks[i]);
            free(prog->forks);
            free(prog->input);
            free(prog->philos);
            free(prog);
            return (0);
        }
    }
    return (1);
}

int    init(t_prog *prog, int argc, char **argv)
{
    int *input;
    input = check_args(argc, argv);
    if (!input)
        return (0);
    prog->input = input;
    if (!init_print(prog))
        return (0);
    if (!init_forks(prog))
        return (0);
    if (!init_philos(prog))
        return (0);
    return (1);
}
