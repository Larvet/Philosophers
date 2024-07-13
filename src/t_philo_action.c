/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:49:23 by locharve          #+#    #+#             */
/*   Updated: 2024/07/13 17:18:22 by marvin           ###   ########.fr       */
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
	size_t	start_time;
	size_t	time;

	t_philo_set_state(p, eating);
	p->meal_nbr++;
	p->last_meal_time = get_timestamp() - p->start_time;
//	printf("YOOOOOOOOOOO\tlastmealtime = %lu\tpstarttime = %lu\n",
//		p->last_meal_time, p->start_time); ///
	start_time = get_timestamp();
	time = 0;
	while (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
			&& time < *(p->av[to_eat]) && time < *(p->av[to_die]))
	{
		usleep(500);
		time = get_timestamp() - start_time;
	}
//	printf("time = %lu\tto_die = %lu\t%d\n", time, *(p->av[to_die]), time >= to_die);
//	printf("philo %lu eat returns %d\n", p->index, time >= *(p->av[to_die])); // ?
//	printf("did a philo die ? %d\n", is_there_dead_philo(p->all->philo, *(p->av[nbr]))); //
	if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		return (-1);
	return (time >= *(p->av[to_die])); // ?
//	return (t_philo_wait(*(p->av[to_eat]),
//		*(p->av[to_die]), p->last_meal_time));
}

int	t_philo_sleep(t_philo *p)
{
	size_t	start_time;
	size_t	time;
	size_t	time_td;

	t_philo_set_state(p, sleeping);
	start_time = get_timestamp();
	time = 0;
//	printf("\tlast_mealtime = %lu\n", p->last_meal_time);
	time_td = start_time - p->start_time - p->last_meal_time;
//	printf("\ttd = %lu\n", time_td); 
	while (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
			&& time < *(p->av[to_sleep])
			&& time + time_td < *(p->av[to_die]))
	{
//		printf("\tphilo %lu timetd = %lu\n",
//			p->index, time_td); //
		usleep(500);
		//time_td += get_timestamp() - start_time - time;
		//time += time_td;
		time = get_timestamp() - start_time;
//		time_td += time;
	}
//	pthread_mutex_lock(p->out_m);
//	printf("index = %lu\ttime = %lu\tstart = %lu\tlastmeal = %lu\tto_die = %lu\n",
//			p->index, time, start_time, p->last_meal_time, *(p->av[to_die]));
//	pthread_mutex_unlock(p->out_m);
//	printf("\t\ttime_td = %lu\n", time_td); //
	if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		return (-1);
	return (time + time_td >= *(p->av[to_die]));
//	return (time_td >= *(p->av[to_die]) || is_there_dead_philo(p->all->philo, *(p->av[nbr]))); // ?
	//printf("p_sleep\tindex = %lu\tto_sleep = %lu\n",
	//	p->index, *(p->av[to_sleep])); //
//	return (t_philo_wait(*(p->av[to_sleep]),
//		*(p->av[to_die]), get_timestamp()));
}