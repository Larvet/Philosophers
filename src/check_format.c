/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:12:21 by marvin            #+#    #+#             */
/*   Updated: 2024/06/11 16:12:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	isonly_digit(char *str)
{
	return (str && (!*str || (ft_isdigit(*str) && isonly_digit(str + 1))));
}

static size_t	size_t_check(char *str)
{
	size_t	result;
	size_t	tmp;
	size_t	i;

	result = 0;
	i = 0;
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	while (str && str[i] && ft_isdigit(str[i]))
	{
		tmp = str[i] - 48 + result * 10;
		if (tmp < result)
			return (0);
		result = tmp;
		i++;
	}
	return (result);
}

int	check_format(char **av)
{
	int	i;

	i = 0;
	while (av && av[i] && ft_strlen(av[i]) > 0
			&& isonly_digit(av[i]) && size_t_check(av[i]))
		i++;
	return (av && i > 0 && !av[i]);
}
