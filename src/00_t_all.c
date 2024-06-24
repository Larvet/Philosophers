/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_t_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:24:31 by marvin            #+#    #+#             */
/*   Updated: 2024/06/24 16:01:27 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*t_error_set(t_all *all, t_error error)
{
	all->error = error;
	return (NULL);
}

unsigned long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	t_all_init(t_all *all, int ac, char **av)
{
	all->av = parse_args(all, ac, av);
	if (!all->av)
		return (1);
	all->mutex = calloc(*(all->av[nbr]), sizeof(pthread_mutex_t)); // ft_calloc
	if (!all->mutex)
		return (2);
	all->philo = t_philotab_init(all);
	all->start_time = get_timestamp();
	return (0);
}

void	t_all_destroy(t_all *all)
{
	if (all->philo)
	{
		free(all->philo);
		//t_philotab_free(all->philo);
	}
	if (all->av)
		size_tptrtab_free(all->av);
}

void	t_all_print(t_all *all)
{
	printf("AV---------------------\n");
	size_tptrtab_print(all->av);
	printf("PHILOS-----------------\n");
	t_philotab_print(all->philo);
}
