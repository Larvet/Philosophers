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

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static int	is_empty_str_in_tab(char **av)
{
	int	i;

	i = 0;
	while (av && av[i] && ft_strlen(av[i]) > 0)
		i++;
	return (av && av[i]);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	isonly_digit(char *str)
{
	return (str && (!*str || (ft_isdigit(*str) && isonly_digit(str + 1))));
}

int	check_format(char **av)
{
	return (!is_empty_str_in_tab(av) && isonly_digit(*av));
}
