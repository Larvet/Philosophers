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

size_t	*ft_atosize_t(char *str)
{
	size_t	*result;
	size_t	tmp;
	size_t	i;

	result = malloc(sizeof(size_t));
	if (!result)
		return (NULL);
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
			return (NULL);
		}
		*result = tmp;
		i++;
	}
	return (result);
}

void	size_tptrtab_free(size_t **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

size_t	**parse_args(t_all *all, int ac, char **av)
{
	size_t			**result;
	int				i;

	result = ft_calloc(ac + 1, sizeof(size_t *));
	if (!result)
		return (t_error_set(&all->error, err_malloc));
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
		size_tptrtab_free(result);
		return (t_error_set(&all->error, err_invalid_arg));
	}
	return (result);
}
