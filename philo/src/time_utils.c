/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:32:16 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/05 23:33:20 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	get_time(struct timeval start)
{
	return ((int)(get_timestamp_ms() - ((start.tv_sec * 1000) + (start.tv_usec
				/ 1000))));
}

long	diff(struct timeval start, struct timeval end)
{
	return ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec)
		/ 1000);
}
