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

/* void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
		&& (!p->av[must_eat] || p->meal_nbr < *(p->av[must_eat])))
	{
		// think
		t_philo_set_state(p, thinking);
		// lock 2
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr])
				&& t_philo_mutex_lock_hub(p)) // set_state
		{
			//printf("coucou\n"); //
			t_philo_set_state(p, dead);
		}
		// eat
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr])
				&& t_philo_eat(p))	// set_state
			t_philo_set_state(p, dead);
		// unlock 2
		//p->f[0].taken = 0;
		//p->f[1].taken = 0;
		printf("taken 0 = %lu\t1 = %lu\n", p->f[0].taken, p->f[1].taken);
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr]))
			t_philo_unlock_hub(p);
		// sleep
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr])
				&& t_philo_sleep(p)) // set state
			t_philo_set_state(p, dead);
	}
	return (NULL);
} */

/* void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	// p->last_meal_time = get_timestamp();
	//printf("index %lu last meal time = %lu\n", p->index, p->last_meal_time); ///
	// p->start_time = p->last_meal_time;
	t_philo_set_state(p, thinking);
	while ((!p->av[must_eat] || p->meal_nbr < *(p->av[must_eat]))
		&& !is_there_dead_philo(p->all->philo, *(p->av[nbr])) && p->state != dead)
	{
		//usleep(500); //////
		if (t_philo_odd_or_even_mutex(p, t_philo_lock_mutex, 0))
			return (NULL);
		t_philo_set_state(p, eating);
		//printf("ouaiiiiiis\n");
		p->last_meal_time = get_timestamp(); ///
		if (t_philo_eat(p))
		{
			//printf("hello from thread %lu\n", p->index); ///
			t_philo_set_state(p, dead);
			return (NULL);
		}
		p->meal_nbr++;
		//printf("ouaiiiiiis mais nan\n");
		if (t_philo_odd_or_even_mutex(p, t_philo_unlock_mutex, 1))
			return (NULL);
		//printf("naaaaaaaan\n"); //
		t_philo_set_state(p, sleeping);
		if (t_philo_sleep(p))
		{
			t_philo_set_state(p, dead);
			return (NULL);
		}
		t_philo_set_state(p, thinking);
	}
	return (NULL);
} */

t_error	t_philotab_thcreate(t_philo *p, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		(p + i)->start_time = get_timestamp();
		(p + i)->last_meal_time = (p + i)->start_time;
		if (pthread_create(&(p + i)->thread, NULL, &routine, p + i))
			break ;
		i++;
	}
	if (i < n)
	{
		t_error_set(p->error, err_thcreate);
		return (*(p->error));
	}
	else
		return (err_none);
}

t_error	t_philotab_thjoin(t_philo *p, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && !pthread_join(p[i].thread, NULL))
		i++;
	if (i < n)
	{
		t_error_set(p->error, err_thjoin);
		return (*(p->error));
	}
	else
		return (err_none);
}
