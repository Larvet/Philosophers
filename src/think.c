/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:29:31 by locharve          #+#    #+#             */
/*   Updated: 2024/07/16 20:07:28 by marvin           ###   ########.fr       */
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
		usleep(1);
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
		t_philo_set_state(p, dead);
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

static int	lmtime_is_oldest(t_philo *ptab, size_t index)
{
	size_t	p_lmt;
	size_t	i;
	size_t	n;

	p_lmt = (ptab + (index - 1))->last_meal_time;
	i = 0;
	n = *(ptab->av[nbr]);
	while (i < n)
	{
		if (i != index - 1 && (ptab + i)->last_meal_time < p_lmt)
			break ;
		i++;
	}
	return (i == n);
}

int	t_philo_think(t_philo *p)
{
	t_philo_set_state(p, thinking);

	if (p->index % 2
			|| (p->meal_nbr > 0 && !lmtime_is_oldest(p->all->philo, p->index)))
	{
		usleep(200);
		while (p->meal_nbr > 0 && !lmtime_is_oldest(p->all->philo, p->index))
			usleep(1);
			// possible boucle infinie
	}
	if (p->index % 2)
	{
		if (t_philo_take_fork(p, p->f[0]) == dead)
			return (1);
		if (t_philo_take_fork(p, p->f[1]) == dead)
			return (1);
	}
	else
	{
		if (t_philo_take_fork(p, p->f[1]) == dead)
			return (1);
		if (t_philo_take_fork(p, p->f[0]) == dead)
			return (1);		
	}
	return (0);
}