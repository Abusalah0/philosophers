/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:31:53 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/05 23:31:29 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	accurate_sleep(long ms)
{
	long	start_time;
	long	end_time;

	start_time = get_timestamp_ms();
	end_time = start_time + ms;
	while (get_timestamp_ms() < end_time)
		usleep(500);
}

void	sleep_philo(t_philo *philo, int time)
{
	int	elapsed;
	int	sleep_time;

	if (!should_stop(philo))
	{
		print_with_lock(philo, "is sleeping");
		elapsed = 0;
		while (elapsed < time && !should_stop(philo))
		{
			if (time - elapsed < 10)
				sleep_time = time - elapsed;
			else
				sleep_time = 10;
			usleep(sleep_time * 1000);
			elapsed += sleep_time;
		}
	}
}
