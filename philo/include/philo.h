/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:53:54 by abdsalah          #+#    #+#             */
/*   Updated: 2025/02/24 13:21:50 by ahramada         ###   ########.fr       */
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
    pthread_t id;
    int num_of_eat;
    struct timeval start;
    struct timeval last_eat;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *print;
}   t_philo;

typedef struct s_prog
{
    int *input;
    pthread_mutex_t *forks;
    t_philo *philos;
    pthread_mutex_t *print;
}   t_prog;

int		*check_args(int argc, char **argv);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
int		ft_isdigit(int c);
int     start(t_prog *prog);
int     init(t_prog *prog, int argc, char **argv);
void    free_prog(t_prog *prog);
void    *routine();

#endif