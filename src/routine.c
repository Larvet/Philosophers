/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:16:18 by locharve          #+#    #+#             */
/*   Updated: 2024/07/13 19:50:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_there_dead_philo(t_philo *ptab, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_lock(&ptab[i].state_m);
		if (ptab[i].state == dead)
		{
			pthread_mutex_unlock(&ptab[i].state_m);
			return (1) ;
		}
		pthread_mutex_unlock(&ptab[i].state_m);
		i++;
	}
	return (0);
}

// les conditions pour set_dead sont mauvaises.

static void	*one_philo_routine(void *arg)
{
	t_philo	*p;
	size_t	start_ts;
	size_t	time;

	p = (t_philo *)arg;
	start_ts = get_timestamp();
	time = 0;
	t_philo_set_state(p, thinking);
	if (time < *(p->av[to_die]))
	{
		pthread_mutex_lock(p->f[0].mutex); // erreur ?
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
	}
	while (time < *(p->av[to_die]))
	{
		usleep(500);
		time = get_timestamp() - start_ts;
	}
	t_philo_set_state(p, dead);
	pthread_mutex_unlock(p->f[0].mutex);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (*(p->av[nbr]) == 1)
		return (one_philo_routine(arg));
	while (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
		&& (!p->av[must_eat] || p->meal_nbr < *(p->av[must_eat])))
	{
		t_philo_set_state(p, thinking);
		if (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
				&& t_philo_mutex_lock_hub(p) > 0)
			t_philo_set_state(p, dead);
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr]))
		{
			if (t_philo_eat(p) > 0)	// set_state
				t_philo_set_state(p, dead);
			if (p->state == dead || is_there_dead_philo(p->all->philo, *(p->av[nbr])))
			{
				t_philo_unlock_hub(p);
				break ;
			}
		//	else if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		//		break ;
		}
		if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
				break ;
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr]))
			t_philo_unlock_hub(p);
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr])
				&& t_philo_sleep(p) > 0) // set state
			t_philo_set_state(p, dead);
	}
	return (NULL);
}
