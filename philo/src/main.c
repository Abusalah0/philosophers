/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:47:38 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/01 17:06:09 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_prog *prog;
	pthread_t monitor_thread;
	
    prog = malloc(sizeof(t_prog));
    if (!prog)
        return (1);
    if (!init(prog, argc, argv))
        return (1);
    if (!start(prog))
	{
        return (1);
	}
	// Create the monitor thread
	pthread_create(&monitor_thread, NULL, monitor, (void *)prog);

	// Wait for the monitor thread to finish
	pthread_join(monitor_thread, NULL);
	free(prog);
    return (0);
}

