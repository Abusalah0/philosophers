/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:31:53 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/06 18:28:43 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	accurate_sleep(long ms)
{
	long	start;
	long	end;

	start = get_timestamp_ms();
	end = start + ms;
	while (get_timestamp_ms() < end)
		usleep(500);
}

void	sleep_philo(t_philo *philo, int time)
{
	int	elapsed;
	int	sleep_time;

	if (!should_stop(philo))
	{
		print_with_safety(philo, "is sleeping");
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
