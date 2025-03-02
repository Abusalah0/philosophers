/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:36:37 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/01 16:50:44 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int assign_philos(t_prog *prog, struct timeval start, int i, int *input)
{
    /* Initialize the per-philosopher "full" mutex */
    if (pthread_mutex_init(&prog->philos[i].full, NULL) != 0)
    {
        while (--i >= 0)
            pthread_mutex_destroy(&prog->philos[i].full);
        free(prog->philos);
        free(prog->forks);
        free(prog->input);
        free(prog);
        return (0);
    }
    prog->philos[i].input = input;
    prog->philos[i].alive = 1;
    prog->philos[i].number = i + 1;
    prog->philos[i].num_of_eat = 0;
    prog->philos[i].left_fork = &prog->forks[i];
    prog->philos[i].right_fork = &prog->forks[(i + 1) % prog->input[NUM_OF_PHILO]];
    prog->philos[i].start = start;
    prog->philos[i].print = &prog->print;  // assign shared print mutex address
    prog->philos[i].last_eat = start;
    return (1);
}

static int init_print(t_prog *prog)
{
    if (pthread_mutex_init(&prog->print, NULL) != 0)
    {
        free(prog->input);
        free(prog);
        return (0);
    }
    return (1);
}

static int init_philos(t_prog *prog)
{
    int i;
    struct timeval start;
    
    gettimeofday(&start, NULL);
    prog->philos = malloc(sizeof(t_philo) * prog->input[NUM_OF_PHILO]);
    if (!prog->philos)
    {
        free(prog->input);
        free(prog);
        return (0);
    }
    i = -1;
    while (++i < prog->input[NUM_OF_PHILO])
    {
        if (!assign_philos(prog, start, i, prog->input))
            return (0);
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
        if (pthread_mutex_init(&prog->forks[i], NULL) != 0)
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

int init(t_prog *prog, int argc, char **argv)
{
    int *input;
    input = check_args(argc, argv);
    if (!input)
        return (0);
    prog->input = input;
    prog->stop = 0;
    if (!init_print(prog))
        return (0);
    if (!init_forks(prog))
        return (0);
    if (!init_philos(prog))
        return (0);
    return (1);
}
