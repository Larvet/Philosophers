/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_include.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:02:46 by marvin            #+#    #+#             */
/*   Updated: 2024/06/10 18:02:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_INCLUDE_H
# define PHILO_INCLUDE_H

# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

# define THINKING "is thinking"
# define FORK_TAKEN "has taken a fork" // not s state
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define DIED "died"

#endif