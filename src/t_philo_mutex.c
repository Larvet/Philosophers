/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:50:29 by locharve          #+#    #+#             */
/*   Updated: 2024/07/08 16:39:11 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (pthread_mutex_lock(&f->mutex))
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

int	t_philo_mutex_lock_hub(t_philo *p)
{
    if (p->index % 2)
	{
		if (t_philo_mutex_lock(p, &p->f[0]))
			return (1);
		//printf("fork = %lu\n", p->f[0].mutex);
		print_state(get_timestamp() - p->start_time, p->index, FORK_TAKEN);
		if (t_philo_mutex_lock(p, &p->f[1]))
			return (2);
		print_state(get_timestamp() - p->start_time, p->index, FORK_TAKEN);
	}
	else
	{
		if (t_philo_mutex_lock(p, &p->f[1]))
			return (3);
		print_state(get_timestamp() - p->start_time, p->index, FORK_TAKEN);
		if (t_philo_mutex_lock(p, &p->f[0]))
			return (4);
		print_state(get_timestamp() - p->start_time, p->index, FORK_TAKEN);
	}
	return (0);
}

static void	t_philo_mutex_unlock(t_fork *f)
{
	pthread_mutex_unlock(&f->mutex);
	f->taken = 0;
}

void	t_philo_unlock_hub(t_philo *p)
{
	if (p->index % 2)
	{
		t_philo_mutex_unlock(&p->f[1]);
		t_philo_mutex_unlock(&p->f[0]);
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