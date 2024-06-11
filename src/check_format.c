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
	return (av && (!*av || (isonly_digit(*av) && check_format(av + 1))));
}
