/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:29:31 by locharve          #+#    #+#             */
/*   Updated: 2024/07/15 19:22:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_state	t_philo_take_fork(t_philo *p, t_fork *f)
{
	size_t	start_ts;
	size_t	time;
	size_t	time_td;

	start_ts = get_timestamp();
	time = 0;
	time_td = start_ts - p->start_time - p->last_meal_time;
	pthread_mutex_lock(f->mutex);
	while (f->taken != 0 && !is_there_dead_philo(p->all->philo, *(p->av[nbr])))
	{
		pthread_mutex_unlock(f->mutex);
		if (time + time_td >= *(p->av[to_die]))
		{
			t_philo_set_state(p, dead);
			return (p->state);
		}
//		pthread_mutex_unlock(f->mutex);
//		printf("coucou\n");
		usleep(500);
		pthread_mutex_lock(f->mutex);
		time = get_timestamp() - start_ts;
	}
	if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
	{
		pthread_mutex_unlock(f->mutex);
		return (p->state);
	}	
	if (!f->taken && time + time_td < *(p->av[to_die]))
	{
		f->taken = p->index;
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
	}
	else
	{
//		printf("\t%lu ftaken = %lu\ttime+timetd = %lu\tto_die = %lu\n",
//				p->index, f->taken, time + time_td, *(p->av[to_die]));
		t_philo_set_state(p, dead);
	}
	pthread_mutex_unlock(f->mutex);
	return (p->state);
}

void	t_philo_drop_forks(t_philo *p)
{
	if (p->index % 2)
	{
		pthread_mutex_lock(p->f[1]->mutex);
		p->f[1]->taken = 0;
		pthread_mutex_unlock(p->f[1]->mutex);
		pthread_mutex_lock(p->f[0]->mutex);
		p->f[0]->taken = 0;
		pthread_mutex_unlock(p->f[0]->mutex);
	}
	else
	{
		pthread_mutex_lock(p->f[0]->mutex);
		p->f[0]->taken = 0;
		pthread_mutex_unlock(p->f[0]->mutex);
		pthread_mutex_lock(p->f[1]->mutex);
		p->f[1]->taken = 0;
		pthread_mutex_unlock(p->f[1]->mutex);
	}
}

int	t_philo_think(t_philo *p)
{
	t_philo_set_state(p, thinking);
	if (p->index % 2)
	{
		usleep(500);
		if (t_philo_take_fork(p, p->f[0]) == dead)
			return (1);
		if (t_philo_take_fork(p, p->f[1]) == dead)
			return (1);
	}
	else
	{
//		usleep(1000);
		if (t_philo_take_fork(p, p->f[1]) == dead)
			return (1);
		if (t_philo_take_fork(p, p->f[0]) == dead)
			return (1);		
	}
	return (0);
}