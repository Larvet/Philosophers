/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:26:10 by locharve          #+#    #+#             */
/*   Updated: 2024/07/11 19:33:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_there_dead_philo(t_philo *ptab, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ptab[i].state != dead)
		i++;
	return (i < n);
}
/*
static int	t_philo_wait_fork(t_philo *p, t_fork *f)
{
	while (f->taken && get_timestamp() - p->last_meal_time < *(p->av[to_die]))
		usleep(500);
}
*/
void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
		&& (!p->av[must_eat] || p->meal_nbr < *(p->av[must_eat])))
	{
		// think
		t_philo_set_state(p, thinking);
		// lock 2
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr]
			&& t_philo_mutex_lock_hub(p))) // set_state
			t_philo_set_state(p, dead);
		// eat
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr]
			&& t_philo_eat(p)))	// set_state
			t_philo_set_state(p, dead);
		// unlock 2
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr]))
			t_philo_unlock_hub(p);
		// sleep
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr]
			&& t_philo_sleep(p))) // set state
			t_philo_set_state(p, dead);
	}
	return (NULL);
}