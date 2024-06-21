/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_t_philo_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:00:52 by locharve          #+#    #+#             */
/*   Updated: 2024/06/21 16:00:52 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_error	lock_mutex(t_philo *p)
{
	if (p->index % 2)
	{
		if (pthread_mutex_lock(&p->mutex[0]) || pthread_mutex_lock(&p->mutex[1]))
			return (err_mlock);
	}
	else
	{
		if (pthread_mutex_lock(&p->mutex[1]) || pthread_mutex_lock(&p->mutex[0]))
			return (err_mlock);
	}
}

t_error	unlock_mutex(t_philo *p)
{
	if (p->index % 2)
	{
		if (pthread_mutex_unlock(&p->mutex[1]) || pthread_mutex_unlock(&p->mutex[0]))
			return (err_munlock);
	}
	else
	{
		if (pthread_mutex_unlock(&p->mutex[0]) || pthread_mutex_unlock(&p->mutex[1]))
			return (err_munlock);
	}
}

void	*routine(void *arg); // arg == philo[i]
{
	t_philo	*p;

	p = (t_philo *)arg;
	t_philo_change_state(p, thinking);

	while (p->f[0]->taken)
	{
		if (gettimestamp() - p->last_meal_time >= p->av[to_die])
		{
			t_philo_change_state(p, dead);
			return (NULL); //////
		}
		usleep(100);
	}
	
	p->error = lock_mutex(p);
	if (p->error)
		return (NULL); //
	// routine
	p->error = unlock_mutex(p);
	if (p->error)
		return (NULL); //
}

void	*t_philotab_thcreate(t_philo *p, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && pthread_create(&p[i].thread, NULL, &routine, &p[i]))
		i++;
	if (i < n)
		return (t_error_set(p->error, err_thcreate));
	else
		return (p);
}

void	*t_philotab_thjoin(t_philo *p, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && pthread_join(&p[i].thread, &p[i].routine_return))
		i++;
	if (i < n)
		return (t_error_set(p->error, err_thjoin));
	else
		return (p);
}