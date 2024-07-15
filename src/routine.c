/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:16:18 by locharve          #+#    #+#             */
/*   Updated: 2024/07/15 13:24:44 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_there_dead_philo(t_philo *ptab, size_t n)
{
	int	r;
	
	(void) n;	
	pthread_mutex_lock(ptab->stop_m); //
	if (*(ptab->stop))
		r = 1;
	else
		r = 0;
	pthread_mutex_unlock(ptab->stop_m);
	return (r);
/* 	size_t	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_lock(&ptab[i].state_m);
		if (ptab[i].state == dead)
		{
			pthread_mutex_unlock(&ptab[i].state_m);
			return (1) ;
		}
		pthread_mutex_unlock(&ptab[i].state_m);
		i++;
	}
	return (0); */
}

// les conditions pour set_dead sont mauvaises.

static void	*one_philo_routine(void *arg)
{
	t_philo	*p;
	size_t	start_ts;
	size_t	time;

	p = (t_philo *)arg;
	start_ts = get_timestamp();
	time = 0;
	t_philo_set_state(p, thinking);
	if (time < *(p->av[to_die]))
	{
		pthread_mutex_lock(p->f[0].mutex); // erreur ?
		print_state(p->out_m, p->start_time, p->index, FORK_TAKEN);
	}
	while (time < *(p->av[to_die]))
	{
		usleep(500);
		time = get_timestamp() - start_ts;
	}
	t_philo_set_state(p, dead);
	pthread_mutex_unlock(p->f[0].mutex);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (*(p->av[nbr]) == 1)
		return (one_philo_routine(arg));
	while (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
		&& (!p->av[must_eat] || p->meal_nbr < *(p->av[must_eat])))
	{
//		printf("\t%lu 1 ftaken0 = %lu\tftaken1 = %lu\n",
//			p->index, p->f[0].taken, p->f[1].taken);
		if (t_philo_think(p))
			break ;
//		printf("\t%lu 2 ftaken0 = %lu\tftaken1 = %lu\n",
//			p->index, p->f[0].taken, p->f[1].taken);
/* 		t_philo_set_state(p, thinking);
		if (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
				&& t_philo_mutex_lock_hub(p))
			break ; */
		//	t_philo_set_state(p, dead);
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr]))
		{
			if (t_philo_eat(p) > 0)	// set_state
				t_philo_set_state(p, dead);
			if (p->state == dead || is_there_dead_philo(p->all->philo, *(p->av[nbr])))
			{
				t_philo_drop_forks(p);
				//t_philo_unlock_hub(p);
				break ;
			}
		//	else if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		//		break ;
		}
	//	if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
	//			break ;
	//	if (!is_there_dead_philo(p->all->philo, *p->av[nbr]))
	//		t_philo_unlock_hub(p);
//		printf("\t%lu 1 ftaken0 = %lu\tftaken1 = %lu\n",
//			p->index, p->f[0].taken, p->f[1].taken);
		t_philo_drop_forks(p);
//		printf("\t%lu 2 ftaken0 = %lu\tftaken1 = %lu\n",
//			p->index, p->f[0].taken, p->f[1].taken);
		if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
			break ;
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr])
				&& t_philo_sleep(p) > 0) // set state
			t_philo_set_state(p, dead);
	}
	return (NULL);
}
