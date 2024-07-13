/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:50:29 by locharve          #+#    #+#             */
/*   Updated: 2024/07/13 17:21:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	t_philo_mutex_lock(t_philo *p, t_fork *f)
{
	size_t	start_ts;
	size_t	time;
	size_t	time_td;
	//printf("coucou\n");
	pthread_mutex_lock(f->mutex);
	//printf("popo\n");
//	printf("\t%lu ftaken 1 = %lu\n", p->index, f->taken);
//	printf("gts = %lu\tlmt = %lu\n", get_timestamp(), p->last_meal_time);
	start_ts = get_timestamp();
	time = 0;
//	printf("\tstart_ts = %lu\tpstarttime = %lu\tplastmealtime = %lu\n",
//		start_ts, p->start_time, p->last_meal_time); //
	time_td = start_ts - p->start_time - p->last_meal_time;
// while: && get_timestamp() - p->start_time - p->last_meal_time < *(p->av[to_die])
	while (f->taken && time + time_td < *(p->av[to_die])
			&& !is_there_dead_philo(p->all->philo, *(p->av[nbr]))) //
	{
//		printf("-");
		printf("time %lu + timetd %lu = %lu\n", time, time_td, time + time_td);
		pthread_mutex_unlock(f->mutex);
		usleep(500);
		pthread_mutex_lock(f->mutex);
		time = get_timestamp() - start_ts;
	}
//	printf("\n");
//printf("\ttime = %lu\ttime_td = %lu\n", time, time_td); ///
	if (time + time_td >= *(p->av[to_die]))
		return (2); //////
	if (!f->taken)
	{
		f->taken = p->index;
		return (0);
	}
	else
//	if (f->taken || is_there_dead_philo(p->all->philo, *(p->av[nbr]))) //
	{
		//printf("\tDEAD\n");
		pthread_mutex_unlock(f->mutex);
		return (1);
	}
//	else
//	{
//		f->taken = p->index;
//		printf("\t%lu ftaken 2 = %lu\n", p->index, f->taken);
//		return (0);
//	}
}
/*
static int	t_philo_mutex_lock(t_philo *p, t_fork *f)
{	// proteger les lock/unlock ?
	pthread_mutex_lock(&f->taken_m);
	while (f->taken && get_timestamp() - p->last_meal_time < *(p->av[to_die]))
	{
		pthread_mutex_unlock(&f->taken_m);
		usleep(500);
		pthread_mutex_lock(&f->taken_m);
	}
	if (f->taken)
	{
		pthread_mutex_unlock(&f->taken_m);
		//t_philo_set_state(p, dead);
		return (1); //dead
	}
	pthread_mutex_unlock(&f->taken_m);
	if (pthread_mutex_lock(f->mutex))
	{
		//pthread_mutex_unlock(&p->fork_m);
		//printf("coucou\n");
		return (2);
	}
	pthread_mutex_lock(&f->taken_m);
	f->taken = p->index;
	pthread_mutex_unlock(&f->taken_m);
	return (0);
}
*/

void	print_mutex(char *str);

int	t_philo_mutex_lock_hub(t_philo *p)
{
    if (p->index % 2)
	{
		usleep(500); //
		if (t_philo_mutex_lock(p, &p->f[0]))
			return (1);	
//		printf("\tfork taken= %p\n", p->f[0].mutex);
//		printf("\t%lu ftaken 3 = %lu\n", p->index, p->f[0].taken); //
		if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		{
			pthread_mutex_unlock(p->f[0].mutex);
			return (-1);
		}
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
		if (t_philo_mutex_lock(p, &p->f[1]))
			return (2);
//		printf("\tfork taken= %p\n", p->f[1].mutex);
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
//		printf("\tfork taken= %p\n", p->f[1].mutex);
		if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		{
			pthread_mutex_unlock(p->f[1].mutex);
			return (-1);
		}
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
		if (t_philo_mutex_lock(p, &p->f[0]))
			return (4);
//		printf("\tfork taken= %p\n", p->f[0].mutex);
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
//		printf("\t%lu unlocked %p\n", p->index, p->f[1].mutex);
		t_philo_mutex_unlock(&p->f[0]);
//		printf("\t%lu unlocked %p\n", p->index, p->f[0].mutex);
		/* pthread_mutex_unlock(&p->f[1].mutex);
		f[1]->taken = 0;
		pthread_mutex_unlock(&p->f[0].mutex);
		f[0]->taken = 0; */
	}
	else
	{
		t_philo_mutex_unlock(&p->f[0]);
		t_philo_mutex_unlock(&p->f[1]);
		/* pthread_mutex_unlock(&p->f[0].mutex);
		f[0]->taken = 0;
		pthread_mutex_unlock(&p->f[1].mutex);
		f[1]->taken = 0; */
	}
}