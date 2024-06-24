/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_lock_mutex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:12:21 by locharve          #+#    #+#             */
/*   Updated: 2024/06/24 16:30:35 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_error	t_philo_lock_mutex(t_philo *p, t_fork *f)
{
	while (f->taken)
	{
		if (gettimestamp() - p->last_meal_time >= p->av[to_die])
		{
			t_philo_set_state(p, dead); //
			return (err_dead); //
		}
		usleep(500);
	}
	if (!pthread_mutex_lock(&f->mutex))
	{
		printf("%lu %lu %s\n", get_timestamp() - p->start_time,
			p->index, FORK_TAKEN);
		f->taken = 1;
		return (err_none);
	}
	else
		return (err_mlock);
}

t_error	t_philo_unlock_mutex(t_philo *p, t_fork *f)
{
	if (!pthread_mutex_unlock(&f->mutex))
	{
		f->taken = 0;
		return (err_none);
	}
	else
		return (err_munlock);
}

t_error	t_philo_odd_or_even_mutex(t_philo *p,
		t_error f_m(t_philo *, t_fork *), int b)
{
	if ((p->index % 2 && !b) || (!(p->index % 2) && b))
	{
		p->error = f_m(p, &p->f[0]);
		if (p->error)
			return (p->error);
		p->error = f_m(p, &p->f[1]);
		return (p->error);
	}
	else
	{
		p->error = f_m(p, &p->f[1]);
		if (p->error)
			return (p->error);
		p->error = f_m(p, &p->f[0]);
		return (p->error);
	}
}
