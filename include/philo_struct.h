/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:27:16 by marvin            #+#    #+#             */
/*   Updated: 2024/06/10 17:27:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

typedef struct s_philo	t_philo;
typedef int	t_action_f(t_philo philo, size_t t_d, size_t act);
typedef int t_fork_f(t_philo philo);
typedef struct s_all	t_all;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				taken;
}	t_fork;

typedef struct s_philo
{
	size_t			**av;
	size_t			index;
	t_state			state;
	t_fork			f[2];
	pthread_t		thread;
//	void			*routine_return;
/*	t_action_f		eat_action;
	t_action_f		sleep_action;
	t_action_f		think_action;
*/
	size_t			start_time;
	size_t			last_meal_time; // unsigned long ?
	size_t			meal_nbr;
	t_error			error;
}	t_philo;

typedef struct s_all
{
	size_t			**av;
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	unsigned long	start_time;
	t_error			error;
}	t_all;

#endif