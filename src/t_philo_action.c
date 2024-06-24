/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:49:23 by locharve          #+#    #+#             */
/*   Updated: 2024/06/24 15:45:11 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check last_meal_time ? p->state ?

int	t_philo_wait(size_t arg, size_t to_die, size_t last_meal_time)
{
	while (get_timestamp() - last_meal_time < arg
			&& get_timestamp() - last_meal_time < to_die)
		usleep(500);
	return (get_timestamp() - last_meal_time < to_die);
}

int	t_philo_eat(t_philo *p)
{
	t_philo_wait(p->av[to_eat], p->av[to_die] * 1000,
			p->last_meal_time);
}

int	t_philo_sleep(t_philo *p)
{
	t_philo_wait(p->av[to_sleep], p->av[to_die] * 1000,
			p->last_meal_time);
}