/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_t_philo_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:00:52 by locharve          #+#    #+#             */
/*   Updated: 2024/06/24 16:02:31 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	t_philotab_set_start_time(t_philo *p, size_t n)
{
	size_t			i;
	unsigned long	time;

	i = 0;
	time = get_timestamp();
	while (i < n)
	{
		(p + i)->start_time = time;
		(p + i)->last_meal_time = 0;
		i++;
	}
}

t_error	t_philotab_thcreate(t_philo *p, size_t n)
{
	size_t	i;

	t_philotab_set_start_time(p, n);
	i = 0;
	while (i < n)
	{
		if (pthread_create(&(p + i)->thread, NULL, &routine, p + i))
			break ;
		i++;
	}
	if (i < n)
	{
		t_error_set(p->error, err_thcreate);
		return (*(p->error));
	}
	else
		return (err_none);
}

t_error	t_philotab_thjoin(t_philo *p, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && !pthread_join(p[i].thread, NULL))
		i++;
	if (i < n)
	{
		t_error_set(p->error, err_thjoin);
		return (*(p->error));
	}
	else
		return (err_none);
}
