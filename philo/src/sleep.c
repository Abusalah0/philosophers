/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:31:53 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/06 21:51:04 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_and_check(long ms)
{
	long	start;
	long	end;

	start = get_timestamp_in_ms();
	end = start + ms;
	while (get_timestamp_in_ms() < end)
	{
		usleep(500);
	}
}

void	sleep_philo(t_philo *philo, int time)
{
	int	time_slept;
	int	sleep_time;

	if (!judgement_day(philo))
	{
		print_with_safety(philo, "is sleeping");
		time_slept = 0;
		while (time_slept < time && !judgement_day(philo))
		{
			if (time - time_slept < 10)
			{
				sleep_time = time - time_slept;
			}
			else
			{
				sleep_time = 10;
			}
			usleep(sleep_time * 1000);
			time_slept += sleep_time;
		}
	}
}
