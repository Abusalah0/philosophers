/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:01:07 by abdsalah          #+#    #+#             */
/*   Updated: 2025/01/14 17:39:23 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	fill_nums(int *nums, char **argv, int argc)
{
	while (argc > 1)
	{
		*nums = ft_atoi(argv[argc - 1]);
		nums++;
		argc--;
	}
}

static bool	is_valid_input(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		str++;
	if (ft_strlen(str) > 10)
	{
		return (0);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	*check_args(int argc, char **argv)
{
	int	*nums;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (NULL);
	}
	while (argc > 1)
	{
		if (!is_valid_input(argv[argc - 1]))
		{
			printf("Error: Invalid argument\n");
			return (NULL);
		}
		argc--;
	}
	nums = malloc(sizeof(int) * argc);
	if (!nums)
		return (NULL);
	fill_nums(nums, argv, argc);
	return (nums);
}
