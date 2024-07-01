/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_t_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:24:31 by marvin            #+#    #+#             */
/*   Updated: 2024/06/24 16:01:27 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*t_error_set(t_error *to_set, t_error error)
{
	*to_set = error;
	return (NULL);
}

unsigned long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static void	mutextab_init(pthread_mutex_t *mtab, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&mtab[i], NULL); /// retour d'erreur ?
		i++;
	}
}

int	t_all_init(t_all *all, int ac, char **av)
{
	all->av = parse_args(all, ac, av);
	pthread_mutex_init(&all->out_m, NULL);
	if (!all->av)
		return (1); // error
	all->mutex = calloc(*(all->av[nbr]), sizeof(pthread_mutex_t)); // ft_calloc
	mutextab_init(all->mutex, *(all->av[nbr]));
	if (!all->mutex)
		return (2); // error
	all->start_time = get_timestamp();
	all->philo = t_philotab_init(all);
	return (0);
}

static void	mutextab_destroy(pthread_mutex_t *mtab, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&mtab[i]);
		i++;
	}
}

/* static void	out_mutex_destroy(t_philo *p, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&p[i].out_m);
		i++;
	}
} */

void	t_all_destroy(t_all *all)
{
	if (all->mutex)
		mutextab_destroy(all->mutex, *(all->av[nbr]));
	if (all->philo)
	{
		//out_mutex_destroy(all->philo, *(all->av[nbr]));
		free(all->philo);
		//t_philotab_free(all->philo);
	}
	if (all->av)
		size_tptrtab_free(all->av);
	pthread_mutex_destroy(&all->out_m);
}

void	t_all_print(t_all *all)
{
	printf("AV---------------------\n");
	size_tptrtab_print(all->av);
	printf("PHILOS-----------------\n");
	t_philotab_print(all->philo);
}
