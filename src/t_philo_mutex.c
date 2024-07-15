/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:50:29 by locharve          #+#    #+#             */
/*   Updated: 2024/07/13 19:59:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	t_philo_mutex_lock(t_philo *p, t_fork *f)
{
	size_t	start_ts;
	size_t	time;
	size_t	time_td;
	
	pthread_mutex_lock(f->mutex);
	start_ts = get_timestamp();
	time = 0;
	time_td = start_ts - p->start_time - p->last_meal_time;
	while (f->taken && time + time_td < *(p->av[to_die])
			&& !is_there_dead_philo(p->all->philo, *(p->av[nbr]))) //
	{
		printf("time %lu + timetd %lu = %lu\n", time, time_td, time + time_td);
		pthread_mutex_unlock(f->mutex);
		usleep(500);
		pthread_mutex_lock(f->mutex);
		time = get_timestamp() - start_ts;
	}
	if (time + time_td >= *(p->av[to_die])
			|| is_there_dead_philo(p->all->philo, *(p->av[nbr])))
	{
		pthread_mutex_unlock(f->mutex);		
		return (2); //////
	}
	if (f->taken)
	{
		pthread_mutex_unlock(f->mutex);
		return (1);
	}
	else
	{
		f->taken = p->index;
		return (0);
	}
}

int	t_philo_mutex_lock_hub(t_philo *p)
{
    if (p->index % 2)
	{
		usleep(500); //
		if (t_philo_mutex_lock(p, &p->f[0]))
			return (1);
		if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		{
			pthread_mutex_unlock(p->f[0].mutex);
			return (-1);
		}
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
		if (t_philo_mutex_lock(p, &p->f[1]))
			return (2);
		if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		{
			pthread_mutex_unlock(p->f[1].mutex);
			pthread_mutex_unlock(p->f[0].mutex);
			return (-1);
		}
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
	}
	else
	{
		if (t_philo_mutex_lock(p, &p->f[1]))
			return (3);
		if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		{
			pthread_mutex_unlock(p->f[1].mutex);
			return (-1);
		}
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
		if (t_philo_mutex_lock(p, &p->f[0]))
			return (4);
		if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		{
			pthread_mutex_unlock(p->f[0].mutex);
			pthread_mutex_unlock(p->f[1].mutex);
			return (-1);
		}
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
	}
	return (0);
}

static void	t_philo_mutex_unlock(t_fork *f)
{
	pthread_mutex_unlock(f->mutex);
	f->taken = 0;
}

void	t_philo_unlock_hub(t_philo *p)
{
	if (p->index % 2)
	{
		t_philo_mutex_unlock(&p->f[1]);
		t_philo_mutex_unlock(&p->f[0]);
	}
	else
	{
		t_philo_mutex_unlock(&p->f[0]);
		t_philo_mutex_unlock(&p->f[1]);
	}
}