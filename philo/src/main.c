/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:47:38 by abdsalah          #+#    #+#             */
/*   Updated: 2025/02/24 05:21:33 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_prog *prog;
	
	prog = malloc(sizeof(t_prog));
	if (!prog)
		return (1);
	if (!init(prog, argc, argv))
		return (1);
	if (!start(prog))
		return (1);
	return (0);
}
