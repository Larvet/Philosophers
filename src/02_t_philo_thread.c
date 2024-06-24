/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_t_philo_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:00:52 by locharve          #+#    #+#             */
/*   Updated: 2024/06/24 16:02:31 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* t_error	t_philo_lock_mutex(t_philo *p)
{
	if (p->index % 2)
	{
		if (!pthread_mutex_lock(&p->mutex[0]))
		{
			printf("%lu %lu %s\n", get_timestamp() - p->start_time,
				p->index, FORK_TAKEN);
			if (!pthread_mutex_lock(&p->mutex[1]))
			{
				printf("%lu %lu %s\n", get_timestamp() - p->start_time,
					p->index, FORK_TAKEN);
				return (err_none);
			}
		}
		return (err_mlock);
	}
	else
	{
		if (!pthread_mutex_lock(&p->mutex[1]))
		{
			printf("%lu %lu %s\n", get_timestamp() - p->start_time,
				p->index, FORK_TAKEN);
			if (!pthread_mutex_lock(&p->mutex[0]))
			{
				printf("%lu %lu %s\n", get_timestamp() - p->start_time,
					p->index, FORK_TAKEN);
				return (err_none);
			}
		}
		return (err_mlock);
	}
}

t_error	t_philo_unlock_mutex(t_philo *p) //
{
	if (p->index % 2)
	{
		if (pthread_mutex_unlock(&p->mutex[1])
				|| pthread_mutex_unlock(&p->mutex[0]))
			return (err_munlock);
	}
	else
	{
		if (pthread_mutex_unlock(&p->mutex[0])
				|| pthread_mutex_unlock(&p->mutex[1]))
			return (err_munlock);
	}
}
 */
void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	t_philo_set_state(p, thinking);
	while ((!p->av[must_eat] || p->meal_nbr < p->av[must_eat])
		&& p->state != dead)
	{
		if (t_philo_odd_or_even_mutex(p, t_philo_lock_mutex, 0))
			return (NULL);
		p->last_meal_time = t_philo_set_state(p, eating);
		if (t_philo_eat(p))
		{
			t_philo_set_state(p, dead);
			return (NULL);
		}
		p->meal_nbr++;
		if (t_philo_odd_or_even_mutex(p, t_philo_unlock_mutex, 1))
			return (NULL);
		t_philo_set_state(p, sleeping);
		if (t_philo_sleep(p))
		{
			t_philo_set_state(p, dead);
			return (NULL);
		}
		t_philo_set_state(p, thinking);
	}
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
	while (i < n && pthread_join(&p[i].thread, NULL))
		i++;
	if (i < n)
		return (t_error_set(p->error, err_thjoin));
	else
		return (p);
}
