/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_t_philo_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:03:53 by marvin            #+#    #+#             */
/*   Updated: 2024/06/11 20:03:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*t_philotab_thcreate(t_philo *p, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && pthread_create(&p[i].thread, NULL, &routine, &p[i]))
		i++;
	if (i < n)
		return (t_error_set(p->error, err_thcreate));
	else
		return (p);
}

void	*t_philotab_thjoin(t_philo *p, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && pthread_join(&p[i].thread, &p[i].routine_return))
		i++;
	if (i < n)
		return (t_error_set(p->error, err_thjoin));
	else
		return (p);
}