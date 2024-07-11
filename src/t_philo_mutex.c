/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:50:29 by locharve          #+#    #+#             */
/*   Updated: 2024/07/11 17:09:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	t_philo_mutex_lock(t_philo *p, t_fork *f)
{
	//printf("coucou\n");
	pthread_mutex_lock(f->mutex);
	//printf("popo\n");
	while (f->taken && get_timestamp() - p->last_meal_time < *(p->av[to_die])
			&& !is_there_dead_philo(p->all->philo, *(p->av[nbr]))) //
	{
		pthread_mutex_unlock(f->mutex);
		usleep(500);
		pthread_mutex_lock(f->mutex);
	}
	if (f->taken || is_there_dead_philo(p->all->philo, *(p->av[nbr]))) //
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
		if (t_philo_mutex_lock(p, &p->f[0]))
			return (1);
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
		printf("\tfork taken= %p\n", p->f[0].mutex);
		if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		{
			pthread_mutex_unlock(p->f[0].mutex);
			return (1);
		}
		if (t_philo_mutex_lock(p, &p->f[1]))
			return (2);
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
		printf("\tfork taken= %p\n", p->f[1].mutex);
		if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		{
			pthread_mutex_unlock(p->f[1].mutex);
			pthread_mutex_unlock(p->f[0].mutex);
			return (1);
		}

	}
	else
	{
		if (t_philo_mutex_lock(p, &p->f[1]))
			return (3);
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
		printf("\tfork taken= %p\n", p->f[1].mutex);
		if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		{
			pthread_mutex_unlock(p->f[1].mutex);
			return (1);
		}
		if (t_philo_mutex_lock(p, &p->f[0]))
			return (4);
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
		printf("\tfork taken= %p\n", p->f[0].mutex);
		if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		{
			pthread_mutex_unlock(p->f[0].mutex);
			pthread_mutex_unlock(p->f[1].mutex);
			return (1);
		}
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