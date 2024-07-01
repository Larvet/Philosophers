/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:49:23 by locharve          #+#    #+#             */
/*   Updated: 2024/07/01 16:09:45 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check last_meal_time ? p->state ?

int	t_philo_wait(size_t arg, size_t to_die, size_t last_meal_time)
{
	//printf("wait arg = %lu\tto_die = %lu\n", arg, to_die);
	size_t	a = get_timestamp() - last_meal_time;
	//printf("a = %lu\n", a); ///
	while (a <= arg && a <= to_die)
	{
		usleep(5000);
		a = get_timestamp() - last_meal_time;
		//printf("a = %lu\targ = %lu\tto_die = %lu\n", a, arg, to_die);
	}
/* 	while (get_timestamp() - last_meal_time < arg
		&& get_timestamp() - last_meal_time < to_die)
	{
		//printf("boucle infinie ?\n"); //
		usleep(500);
	} */
	//printf("p_wait = %lu\t%lu\t%d\n", last_meal_time, to_die, get_timestamp() - last_meal_time < to_die);
	return (!(get_timestamp() - last_meal_time < to_die));
	// 0 : ok ; 1 : dead
}

int	t_philo_eat(t_philo *p)
{
	return (t_philo_wait(*(p->av[to_eat]) * 1000,
		*(p->av[to_die]) * 1000, p->last_meal_time));
}

int	t_philo_sleep(t_philo *p)
{
	//printf("p_sleep\tindex = %lu\tto_sleep = %lu\n",
	//	p->index, *(p->av[to_sleep])); //
	return (t_philo_wait(*(p->av[to_sleep]) * 1000,
		*(p->av[to_die]) * 1000, p->last_meal_time));
}