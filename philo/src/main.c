/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:03:53 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/06 18:15:06 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_prog	*prog;

	prog = malloc(sizeof(t_prog));
	if (!prog)
		return (1);
	memset(prog, 0, sizeof(t_prog));
	if (!init(prog, argc, argv))
	{
		free(prog);
		return (1);
	}
	if (!start(prog))
	{
		free_prog(prog, 1, 1, 1);
		free(prog);
		return (1);
	}
	free_prog(prog, 1, 1, 1);
	free(prog);
	return (0);
}
