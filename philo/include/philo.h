/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:33:11 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/05 23:33:12 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

enum				e_args
{
	NUM_OF_PHILO,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUM_TO_EAT,
};

typedef struct s_philo
{
	int				number;
	pthread_t		id;
	int				meal_count;
	struct timeval	start;
	struct timeval	last_eat;
	pthread_mutex_t	last_eat_mutex;
	int				*input;
	int				*shared_stop;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*stop_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print;
}					t_philo;

typedef struct s_prog
{
	int				stop;
	struct timeval	start_time;
	int				*input;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	stop_mutex;
}					t_prog;

int					*check_args(int argc, char **argv);
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *str);
int					ft_isdigit(int c);
int					start(t_prog *prog);
int					init(t_prog *prog, int argc, char **argv);
void				free_prog(t_prog *prog, bool forks, bool philos,
						bool mutexes);
void				*routine(void *philo);
int					eat(t_philo *philo);
void				sleep_philo(t_philo *philo, int time);
int					get_time(struct timeval start);
void				*monitor(void *ptr);
int					should_stop(t_philo *philo);
void				print_with_lock(t_philo *philo, char *status);
long				diff(struct timeval start, struct timeval end);
void				accurate_sleep(long ms);
void				free_philos(t_prog *prog);
void				free_forks(t_prog *prog);
void				free_mutexes(t_prog *prog);
long				get_timestamp_ms(void);

#endif