/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:16:18 by locharve          #+#    #+#             */
/*   Updated: 2024/07/08 16:38:58 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_there_dead_philo(t_philo *ptab, size_t n)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&ptab[i].state_m);
	while (i < n && ptab[i].state != dead)
	{
		pthread_mutex_unlock(&ptab[i].state_m); 
		i++;
		if (i == n)
			break ;
		pthread_mutex_lock(&ptab[i].state_m);
	}
	return (i < n);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
		&& (!p->av[must_eat] || p->meal_nbr < *(p->av[must_eat])))
	{
		//if (!is_there_dead_philo(p->all->philo, *(p->av[nbr])))
			t_philo_set_state(p, thinking);
		if (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
				&& t_philo_mutex_lock_hub(p))
			t_philo_set_state(p, dead);
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr])
				&& t_philo_eat(p))	// set_state
			t_philo_set_state(p, dead);
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr]))
			t_philo_unlock_hub(p);
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr])
				&& t_philo_sleep(p)) // set state
			t_philo_set_state(p, dead);
	}
	return (NULL);
}