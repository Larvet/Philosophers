/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:49:23 by locharve          #+#    #+#             */
/*   Updated: 2024/07/03 15:49:25 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check last_meal_time ? p->state ?

int	t_philo_wait(size_t arg, size_t to_die, size_t last_meal_time)
{
	//printf("wait arg = %lu\tto_die = %lu\n", arg, to_die);
	size_t	a = get_timestamp() - last_meal_time;
	//printf("a = %lu\n", a); ///
	while (a < arg && a < to_die)
	{
		usleep(500);
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
	t_philo_set_state(p, eating);
	p->meal_nbr++;
	p->last_meal_time = get_timestamp();
	return (t_philo_wait(*(p->av[to_eat]),
		*(p->av[to_die]), p->last_meal_time));
}

int	t_philo_sleep(t_philo *p)
{
	t_philo_set_state(p, sleeping);
	//printf("p_sleep\tindex = %lu\tto_sleep = %lu\n",
	//	p->index, *(p->av[to_sleep])); //
	return (t_philo_wait(*(p->av[to_sleep]),
		*(p->av[to_die]), p->last_meal_time));
}