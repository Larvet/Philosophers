/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_t_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:06:36 by locharve          #+#    #+#             */
/*   Updated: 2024/06/24 15:47:58 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_error	t_fork_init(t_all *all, t_fork *f, size_t i)
{
	if (pthread_mutex_init(&f->taken_m, NULL))
	{
		t_error_set(&all->error, err_minit);
		return (all->error);
	}
	f->mutex = all->mutex + i;
	f->taken = 0;
	return (err_none);
}

t_error	t_philo_init(t_all *all, t_philo *p, size_t i)
{
	p->all = all;
	p->av = all->av;
	p->index = i + 1;
	p->state = init;
	p->out_m = &all->out_m;
	p->stop_m = &all->stop_m;
	if (pthread_mutex_init(&p->state_m, NULL))
	{
		t_error_set(&all->error, err_minit);
		return (all->error);
	}
	if (t_fork_init(all, &p->f[0], i))
		return (all->error);
	if (i < *(all->av[nbr]) - 1)
	{
		t_fork_init(all, &p->f[1], i + 1);
	}
	else
	{
		t_fork_init(all, &p->f[1], 0);
	}
	p->meal_nbr = 0;
	p->error = &all->error;
	p->stop = &all->stop;
	return (err_none);
}

void	t_philotab_print(t_philo *p)
{
	size_t	n;
	size_t	i;

	n = *(p->av[nbr]);
	i = 0;
	while (i < n)
	{
		printf("index = %lu\n", p[i].index);
		i++;
	}
}

t_error	t_philotab_free(t_philo *p, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && p && !pthread_mutex_destroy(&p[i].f[0].taken_m)
			&& !pthread_mutex_destroy(&p[i].f[1].taken_m))
		i++;
	if (i < n)
	{
		t_error_set(p->error, err_mdestroy);
		return (*(p->error)); // free p ?
	}
	free(p);
	return (err_none);
}

t_philo	*t_philotab_init(t_all *all)
{
	t_philo	*result;
	size_t	i;
	size_t	n;

	n = *(all->av[nbr]);
	result = calloc(n, sizeof(t_philo));
	if (!result)
		return (t_error_set(&all->error, err_malloc));
	i = 0;
	while (i < n)
	{
		if (t_philo_init(all, &result[i], i))
		{
			t_philotab_free(result, n);
			return (NULL);
		}
		i++;
	}
	return (result);
}

char	*get_state_str(t_state state)
{
	if (state == dead)
		return (DIED);
	else if (state == eating)
		return (EATING);
	else if (state == sleeping)
		return (SLEEPING);
	else if (state == thinking)
		return (THINKING);
	else
		return (NULL);
}

size_t	t_philo_set_state(t_philo *p, t_state state)
{	// return t_error ?
	pthread_mutex_lock(&p->state_m);
	p->state = state;
	pthread_mutex_lock(p->stop_m);
	if (!(*(p->stop)))
	{
		if (state == dead)
			*(p->stop) = 1;
		pthread_mutex_unlock(p->stop_m);
		print_state(p->out_m, p->start_time, p->index, get_state_str(state));
	}
	pthread_mutex_unlock(&p->state_m);
	return (0);
}

void	print_state(pthread_mutex_t *m, unsigned long time, size_t i, char *str)
{
	pthread_mutex_lock(m);
	printf("%.5lu\t%lu %s\n", get_timestamp() - time, i, str);
	pthread_mutex_unlock(m);
}