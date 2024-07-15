/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:50:29 by locharve          #+#    #+#             */
/*   Updated: 2024/07/15 12:45:16 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	t_philo_stop_unlock(t_philo *p, int n)
{
	if (p->index % 2)
	{
		if (n)
			pthread_mutex_unlock(p->f[1].mutex);
		pthread_mutex_unlock(p->f[0].mutex);
	}
	else
	{
		if (n)
			pthread_mutex_unlock(p->f[0].mutex);
		pthread_mutex_unlock(p->f[1].mutex);
	}
	return (1);
}

static int	t_philo_mutex_lock(t_philo *p, t_fork *f)
{
	size_t	start_ts;
	size_t	time;
	size_t	time_td;

	start_ts = get_timestamp();
	time = 0;
	time_td = start_ts - p->start_time - p->last_meal_time;
	pthread_mutex_lock(f->mutex);
	while (f->taken && time + time_td < *(p->av[to_die])) //
	{
		printf("time %lu + timetd %lu = %lu\n", time, time_td, time + time_td);
		pthread_mutex_unlock(f->mutex);
		usleep(500);
		pthread_mutex_lock(f->mutex);
		time = get_timestamp() - start_ts;
	}
	if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		return (-1); ///
	if (f->taken || time + time_td >= *(p->av[to_die]))
	{
		t_philo_set_state(p, dead);	
		return (1); //////
	}
	else
	{
		f->taken = p->index;
		pthread_mutex_unlock(f->mutex);
		return (0);
	}
}

int	t_philo_mutex_lock_hub(t_philo *p)
{
    if (p->index % 2)
	{
		usleep(200); //
		if (t_philo_mutex_lock(p, &p->f[0]))
			return (t_philo_stop_unlock(p, 0));
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
		if (t_philo_mutex_lock(p, &p->f[1]))
			return (t_philo_stop_unlock(p, 1));
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
	}
	else
	{
		if (t_philo_mutex_lock(p, &p->f[1]))
			return (t_philo_stop_unlock(p, 0));
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
		if (t_philo_mutex_lock(p, &p->f[0]))
			return (t_philo_stop_unlock(p, 1));
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