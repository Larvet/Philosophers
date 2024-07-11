/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:16:18 by locharve          #+#    #+#             */
/*   Updated: 2024/07/11 16:42:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_there_dead_philo(t_philo *ptab, size_t n)
{
	size_t	i;

	i = 0;
	//pthread_mutex_lock(&ptab[i].state_m);
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
		//if (i == n)
		//	break ;
		//pthread_mutex_lock(&ptab[i].state_m);
	}
//	printf("dead philo ? %d\n", i < n);
	return (0);
}

// les conditions pour set_dead sont mauvaises.

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
//	printf("bonjour\n"); //
	while (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
		&& (!p->av[must_eat] || p->meal_nbr < *(p->av[must_eat])))
	{
		pthread_mutex_lock(p->out_m);
//		printf("-------------passage %d philo %lu\n", 0, p->index); //
		pthread_mutex_unlock(p->out_m);

		//if (!is_there_dead_philo(p->all->philo, *(p->av[nbr])))
			t_philo_set_state(p, thinking);

		pthread_mutex_lock(p->out_m);
//		printf("-------------passage %d philo %lu\n", 1, p->index); //
		pthread_mutex_unlock(p->out_m);

		if (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
				&& t_philo_mutex_lock_hub(p))
			t_philo_set_state(p, dead);

		pthread_mutex_lock(p->out_m);
//		printf("-------------passage %d philo %lu\n", 2, p->index); //
		pthread_mutex_unlock(p->out_m);

		if (!is_there_dead_philo(p->all->philo, *p->av[nbr])
				&& t_philo_eat(p))	// set_state
			t_philo_set_state(p, dead);

		pthread_mutex_lock(p->out_m);
//		printf("-------------passage %d philo %lu\n", 3, p->index); //
		pthread_mutex_unlock(p->out_m);

		if (p->state == dead)
		{
			t_philo_unlock_hub(p);
			break ;
		}
		else if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
			break ;
		if (!is_there_dead_philo(p->all->philo, *p->av[nbr]))
			t_philo_unlock_hub(p);

		pthread_mutex_lock(p->out_m);
//		printf("-------------passage %d philo %lu\n", 4, p->index); //
		pthread_mutex_unlock(p->out_m);

		if (!is_there_dead_philo(p->all->philo, *p->av[nbr])
				&& t_philo_sleep(p)) // set state
			t_philo_set_state(p, dead);
	}
//	printf("sortie de boucle %lu\n", p->index);
	return (NULL);
}
