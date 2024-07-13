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

static t_error	mutextab_init(pthread_mutex_t *mtab, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && !pthread_mutex_init(&mtab[i], NULL)) /// retour d'erreur ?
	{
		//printf("mutex %lu addr = %p\n", i, &mtab[i]); //
		i++;
	}
	if (i < n)
		return (err_minit);
	else
		return (err_none);
}

t_error	t_all_init(t_all *all, int ac, char **av)
{
	all->error = err_none;
	all->av = parse_args(all, ac, av);
	//size_tptrtab_print(all->av); //
	if (all->error)
	{
		//printf("ouaiiiiiis\n"); //
		return (all->error);
	}
	all->mutex = ft_calloc(*(all->av[nbr]), sizeof(pthread_mutex_t));
	if (!all->mutex)
	{
		t_error_set(&all->error, err_malloc);
		return (all->error);
	}
	if (mutextab_init(all->mutex, *(all->av[nbr]))
		|| pthread_mutex_init(&all->out_m, NULL))
	{
		t_error_set(&all->error, err_minit);
		return (all->error);
	}
	//all->start_time = get_timestamp(); // start time juste avant pthread_create ?
	all->philo = t_philotab_init(all);
	if (!all->philo)
		return (all->error);
	return (0);
}

static t_error	mutextab_destroy(pthread_mutex_t *mtab, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && !pthread_mutex_destroy(&mtab[i]))
		i++;
	if (i < n)
		return (err_mdestroy);
	else
		return (err_none);
}

void	t_all_destroy(t_all *all)
{
	if (all->mutex)
	{
		if (mutextab_destroy(all->mutex, *(all->av[nbr])))
			t_error_set(&all->error, err_mdestroy);
		free(all->mutex);
	}
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

void	print_error(t_error error)
{
	if (error)
		printf("error %d\n", error); // ft_putstr_fd
	/* if (error == err_malloc)
	else if (error == err_invalid_arg)
	else if (error == err_thcreate)
	else if (error == err_thjoin)
	else if (error == err_minit)
	else if (error == err_mdestroy)
	else if (error == err_mlock)
	else if (error == err_munlock) */
}