/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_ttab_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:47:58 by marvin            #+#    #+#             */
/*   Updated: 2024/06/24 16:01:42 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	size_tptrtab_print(size_t **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[%d] = %lu\n", i, *tab[i]);
		i++;
	}
}
