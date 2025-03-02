/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:53:54 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/01 17:06:18 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

enum e_args
{
    NUM_OF_PHILO,
    TIME_TO_DIE,
    TIME_TO_EAT,
    TIME_TO_SLEEP,
    NUM_TO_EAT,
};

typedef struct s_philo
{
    int number;
    int *input;
    int alive;
    pthread_t id;
    int num_of_eat;
    struct timeval start;
    struct timeval last_eat;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *print;      // pointer to shared print mutex (in t_prog)
    pthread_mutex_t full;        // per-philosopher mutex for protecting num_of_eat
}   t_philo;

typedef struct s_prog
{
    int *input;
    pthread_mutex_t *forks;
    t_philo *philos;
    pthread_mutex_t print;
    int stop;       // shared print mutex (direct member)
}   t_prog;

/* Function Prototypes */
int		*check_args(int argc, char **argv);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
int		ft_isdigit(int c);
int     start(t_prog *prog);
int     init(t_prog *prog, int argc, char **argv);
void    free_prog(t_prog *prog);
void    *routine(void *philo);
void    eat(t_philo *philo);
void    sleep_philo(t_philo *philo, int time);
int     get_time(struct timeval start);
void *monitor(void *ptr);

#endif
