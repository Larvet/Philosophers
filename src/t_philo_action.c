/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:49:23 by locharve          #+#    #+#             */
/*   Updated: 2024/07/11 16:52:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check last_meal_time ? p->state ?
/*
int	t_philo_wait(size_t arg, size_t to_die, size_t last_meal_time)
{
	size_t	a;
	size_t	b;
	int		r;
	
	a = get_timestamp() - last_meal_time;
	b = 0;
	printf("a = %lu\n", a);
	while (b < arg && a + b < to_die)
	{
		//if (a % 5 == 0)
		//	printf("a = %lu\n", a);
		usleep(500);
		a = get_timestamp() - last_meal_time;
		b = a - b;
	}
	//printf("a + b = %lu\n", a + b);
	r = !(get_timestamp() - last_meal_time < to_die);
	printf("time spent = %lu\tto_die = %lu\n", get_timestamp() - last_meal_time, to_die);
	return (r);
	// 0 : ok ; 1 : dead
}
*/
int	t_philo_eat(t_philo *p)
{
	size_t	time;

	t_philo_set_state(p, eating);
	p->meal_nbr++;
	p->last_meal_time = get_timestamp();
	time = 0;
	while (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
			&& time < *(p->av[to_eat]) && time < *(p->av[to_die]))
	{
		usleep(500);
		time = get_timestamp() - p->last_meal_time;
	}
//	printf("time = %lu\tto_die = %lu\t%d\n", time, *(p->av[to_die]), time >= to_die);
	return (time >= *(p->av[to_die]));
//	return (t_philo_wait(*(p->av[to_eat]),
//		*(p->av[to_die]), p->last_meal_time));
}

int	t_philo_sleep(t_philo *p)
{
	size_t	start_time;
	size_t	time;

	t_philo_set_state(p, sleeping);
	start_time = get_timestamp();
	time = start_time;
	while (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
			&& time - start_time < *(p->av[to_eat])
			&& time - p->last_meal_time < *(p->av[to_die]))
	{
		usleep(500);
		time = get_timestamp() - start_time;
	}
	return (time - p->last_meal_time >= *(p->av[to_die]));
	//printf("p_sleep\tindex = %lu\tto_sleep = %lu\n",
	//	p->index, *(p->av[to_sleep])); //
//	return (t_philo_wait(*(p->av[to_sleep]),
//		*(p->av[to_die]), get_timestamp()));
}