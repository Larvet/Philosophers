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

void	t_philo_init(t_all *all, t_philo *p, size_t i)
{
	p->all = all;
	p->av = all->av;
	p->index = i + 1;
	p->state = init;
	pthread_mutex_init(&p->fork_m, NULL); //
	p->out_m = &all->out_m;
	// pthread_mutex_init(&p->out_m, NULL);
	p->f[0].mutex = all->mutex[i];
	p->f[0].taken = 0;
	if (i < *(p->av[nbr]) - 1)
		p->f[1].mutex = all->mutex[i + 1];
	else
		p->f[1].mutex = all->mutex[0];
	p->f[1].taken = 0;
	p->start_time = all->start_time;
	p->last_meal_time = all->start_time;
	p->meal_nbr = 0;
	p->error = all->error;
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
		t_philo_init(all, &result[i], i);
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
{
	size_t	timestamp;

	timestamp = get_timestamp() - p->start_time;
//	printf("set_state :\tgts = %lu\tstart_time = %lu\ttimestamp = %lu\n",
//		get_timestamp(), p->start_time, timestamp);
	pthread_mutex_lock(&p->fork_m);
	p->state = state;
	pthread_mutex_unlock(&p->fork_m);
	pthread_mutex_lock(p->out_m);
	printf("%lu %lu %s\n", timestamp,
		p->index, get_state_str(state));
	pthread_mutex_unlock(p->out_m);
	return (timestamp);
}
