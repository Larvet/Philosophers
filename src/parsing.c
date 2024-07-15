/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:01:09 by marvin            #+#    #+#             */
/*   Updated: 2024/06/24 16:00:38 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

size_t	*ft_atosize_t(char *str)
{
	size_t	*result;
	size_t	tmp;
	size_t	i;

	result = malloc(sizeof(size_t));
	if (!result)
		return (NULL); // malloc error
	*result = 0;
	i = 0;
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	while (str && str[i] && ft_isdigit(str[i]))
	{
		tmp = str[i] - 48 + *result * 10;
		if (tmp < *result)
		{
			free(result);
			return (NULL); // invalid argument
		}
		*result = tmp;
		i++;
	}
	return (result);
}

size_t	**parse_args(t_all *all, int ac, char **av) // rename
{
	size_t			**result;
	int				i;

	result = calloc(ac + 1, sizeof(size_t *)); //
	if (!result)
		return (t_error_set(&all->error, err_malloc)); // malloc error
	i = 0;
	while (i < ac)
	{
		result[i] = ft_atosize_t(av[i]);
		if (!result[i])
			break ;
		i++;
	}
	if (i < ac || *result[0] > 200)
	{
		size_tptrtab_free(result); // invalid argument
		return (t_error_set(&all->error, err_invalid_arg));
	}
	return (result);
}
