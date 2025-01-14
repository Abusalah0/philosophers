/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:01:07 by abdsalah          #+#    #+#             */
/*   Updated: 2025/01/14 17:19:28 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
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
bool check_args(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        return (0);
    while(argc > 1)
    {
        if (!is_valid_input(argv[argc - 1]))
            return (0);
        argc--;
    }
    return (1);
}