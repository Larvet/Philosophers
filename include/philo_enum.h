/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_enum.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:51:22 by marvin            #+#    #+#             */
/*   Updated: 2024/06/11 15:51:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ENUM_H
# define PHILO_ENUM_H

typedef enum e_arg
{
	nbr,
	to_die,
	to_eat,
	to_sleep,
	must_eat
}	t_arg;

typedef enum e_error
{
	err_none,
	err_malloc,
	err_invalid_arg,
	err_thcreate,
	err_thjoin,
	err_minit,
	err_mdestroy,
	err_mlock,
	err_munlock,
	err_dead	// ?
}	t_error;

typedef enum e_state
{
	init,
	dead,
	eating,
	sleeping,
	thinking
}	t_state;

#endif