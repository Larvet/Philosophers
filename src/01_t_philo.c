/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_t_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:37:34 by marvin            #+#    #+#             */
/*   Updated: 2024/06/11 19:37:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg); // arg == philo[i]
{
	/*
		while (hands_full < 2)
	*/
}

void	t_philo_init(t_all *all, t_philo *p, size_t i)
{
	p->av = all->av;
	p->index = i + 1;
	p->error = all->error;
/*	if (pthread_create(&p->thread, NULL, &routine, p) == - 1)
		return ;
*/	
}

void	t_philotab_print(t_philo *p)
{
	size_t	n;
	size_t	i;

	n = *(p->av[nbr]);
	i = 0;
	while (i < n)
	{
		printf("index = %lu\n", p[i].index);
		i++;
	}
}

t_philo	*t_philotab_init(t_all *all)
{
	t_philo	*result;
	size_t	i;
	size_t	n;

	n = *(all->av[nbr]);
	result = calloc(n, sizeof(t_philo));
	if (!result)
		return (t_error_set(all, err_malloc));
	i = 0;
	while (i < n)
	{
		t_philo_init(all, &result[i], i);
		i++;
	}
	return (result);
}
