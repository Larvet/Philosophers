/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:16:18 by locharve          #+#    #+#             */
/*   Updated: 2024/07/16 20:07:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_stop(t_philo *p)
{
	pthread_mutex_lock(p->stop_m);
	*(p->stop) = 1;
	pthread_mutex_unlock(p->stop_m);
}

static int	get_stop(t_philo *p)
{
	int	val;

	pthread_mutex_lock(p->stop_m);
	val = *(p->stop);
	pthread_mutex_unlock(p->stop_m);
	return (val);
}

int	is_there_dead_philo(t_philo *ptab, size_t n)
{
	size_t	i;
//	int	r;
	
	i = 0;
	pthread_mutex_lock(&(ptab + i)->state_m);
	while (i < n && (ptab + i)->state != dead)
	{
//		if ((ptab + i)->state == dead)
//			break ;
		pthread_mutex_unlock(&(ptab + i)->state_m);
		i++;
		pthread_mutex_lock(&(ptab + i)->state_m);
	}
	pthread_mutex_unlock(&(ptab + i)->state_m);
/*	(void) n;	
	pthread_mutex_lock(ptab->stop_m); //
	if (*(ptab->stop))
		r = 1;
	else
		r = 0;
	pthread_mutex_unlock(ptab->stop_m);
*/	return (i < n);
}

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
		pthread_mutex_lock(p->f[0]->mutex);
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
	}
	while (time < *(p->av[to_die]))
	{
		usleep(500);
		time = get_timestamp() - start_ts;
	}
	t_philo_set_state(p, dead);
	pthread_mutex_unlock(p->f[0]->mutex);
	return (NULL);
}

static int	all_philos_ate(t_philo *p)
{
	size_t	s_time;
	size_t	e_time;
	size_t	i;

	if (!p || !p->av[must_eat])
		return (0);
	s_time = p->start_time;
	e_time = *(p->av[to_eat]);
	i = 0;
	while (i < *(p->av[nbr]) && (p + i)->meal_nbr == *((p + i)->av[must_eat])
			&& get_timestamp() - s_time - (p + i)->last_meal_time >= e_time)
		i++;
	return (i == *(p->av[nbr]));
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (*(p->av[nbr]) == 1)
		return (one_philo_routine(arg));
	while (!get_stop(p) && !is_there_dead_philo(p->all->philo, *(p->av[nbr]))
		&& (!p->av[must_eat] || p->meal_nbr < *(p->av[must_eat])))
	{
		if (t_philo_think(p) || get_stop(p)
				|| is_there_dead_philo(p->all->philo, *(p->av[nbr])))
			break ;
		if (!get_stop(p) && !is_there_dead_philo(p->all->philo, *p->av[nbr]))
		{
			if (t_philo_eat(p) > 0)
				t_philo_set_state(p, dead);
			if (p->state == dead
					|| is_there_dead_philo(p->all->philo, *(p->av[nbr])))
				break ;
		}
		t_philo_drop_forks(p);
		if (all_philos_ate(p->all->philo))
		{
			set_stop(p);
			return (NULL);	
		}
		if (get_stop(p) || is_there_dead_philo(p->all->philo, *(p->av[nbr])))
			break ;
		if (!get_stop(p) && !is_there_dead_philo(p->all->philo, *p->av[nbr])
				&& t_philo_sleep(p) > 0)
			t_philo_set_state(p, dead);
		if ((p->av[must_eat] && *(p->av[must_eat]) == p->meal_nbr))
			break ;
	}
	if (p->av[must_eat] && p->state != dead)
		t_philo_set_state(p, thinking);
	return (NULL);
}
