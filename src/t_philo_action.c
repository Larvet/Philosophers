/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:49:23 by locharve          #+#    #+#             */
/*   Updated: 2024/07/13 17:30:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	t_philo_eat(t_philo *p)
{
	size_t	start_time;
	size_t	time;

	t_philo_set_state(p, eating);
	p->meal_nbr++;
	p->last_meal_time = get_timestamp() - p->start_time;
	start_time = get_timestamp();
	time = 0;
	while (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
			&& time < *(p->av[to_eat]) && time < *(p->av[to_die]))
	{
		usleep(500);
		time = get_timestamp() - start_time;
	}
	if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		return (-1);
	return (time >= *(p->av[to_die])); // ?
}

int	t_philo_sleep(t_philo *p)
{
	size_t	start_time;
	size_t	time;
	size_t	time_td;

	t_philo_set_state(p, sleeping);
	start_time = get_timestamp();
	time = 0;
	time_td = start_time - p->start_time - p->last_meal_time;
	while (!is_there_dead_philo(p->all->philo, *(p->av[nbr]))
			&& time < *(p->av[to_sleep])
			&& time + time_td < *(p->av[to_die]))
	{
		usleep(500);
		time = get_timestamp() - start_time;
	}
	if (is_there_dead_philo(p->all->philo, *(p->av[nbr])))
		return (-1);
	return (time + time_td >= *(p->av[to_die]));
}
