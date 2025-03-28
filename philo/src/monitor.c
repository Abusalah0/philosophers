/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:20:59 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/06 21:52:42 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	announce_full(t_prog *prog)
// {
// 	if (!prog->stop)
// 	{
// 		pthread_mutex_lock(&prog->print);
// 		printf("All philosophers have eaten enough times\n");
// 		pthread_mutex_unlock(&prog->print);
// 		prog->stop = 1;
// 	}
// }

int	check_full(t_prog *prog)
{
	int	i;
	int	all_full;

	i = 0;
	all_full = 1;
	if (prog->input[NUM_TO_EAT] == -1)
	{
		return (0);
	}
	while (i < prog->input[NUM_OF_PHILO])
	{
		pthread_mutex_lock(&prog->philos[i].meal_mutex);
		if (prog->philos[i].meal_count < prog->input[NUM_TO_EAT])
		{
			all_full = 0;
			pthread_mutex_unlock(&prog->philos[i].meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&prog->philos[i].meal_mutex);
		i++;
	}
	return (all_full);
}

static int	is_starved(t_prog *prog, int i, long current_time_ms,
		long last_eat_time_ms)
{
	if ((current_time_ms - last_eat_time_ms) > prog->input[TIME_TO_DIE])
	{
		pthread_mutex_lock(&prog->stop_mutex);
		if (!prog->stop)
		{
			pthread_mutex_lock(&prog->print);
			printf("%d %d died\n", get_time(prog->philos[i].start),
				prog->philos[i].number);
			pthread_mutex_unlock(&prog->print);
			prog->stop = 1;
			pthread_mutex_unlock(&prog->stop_mutex);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&prog->stop_mutex);
		}
		return (1);
	}
	return (0);
}

int	check_death(t_prog *prog)
{
	int				i;
	long			current_time_ms;
	long			last_eat_time_ms;
	struct timeval	last_eat_time;

	i = 0;
	current_time_ms = get_timestamp_in_ms();
	while (i < prog->input[NUM_OF_PHILO])
	{
		pthread_mutex_lock(&prog->philos[i].last_eat_mutex);
		last_eat_time = prog->philos[i].last_eat;
		pthread_mutex_unlock(&prog->philos[i].last_eat_mutex);
		last_eat_time_ms = (last_eat_time.tv_sec * 1000)
			+ (last_eat_time.tv_usec / 1000);
		if (is_starved(prog, i, current_time_ms, last_eat_time_ms))
			return (1);
		i++;
	}
	return (0);
}

void	*monitor(void *ptr)
{
	t_prog	*prog;
	int		stop_flag;

	stop_flag = 0;
	prog = (t_prog *)ptr;
	sleep_and_check(1);
	while (!stop_flag)
	{
		if (check_death(prog))
		{
			break ;
		}
		if (check_full(prog))
		{
			pthread_mutex_lock(&prog->stop_mutex);
			prog->stop = 1;
			pthread_mutex_unlock(&prog->stop_mutex);
			break ;
		}
		pthread_mutex_lock(&prog->stop_mutex);
		stop_flag = prog->stop;
		pthread_mutex_unlock(&prog->stop_mutex);
		usleep(500);
	}
	return (NULL);
}
