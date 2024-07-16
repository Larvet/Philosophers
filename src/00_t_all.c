/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_t_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:46:57 by locharve          #+#    #+#             */
/*   Updated: 2024/07/16 14:46:57 by locharve         ###   ########.fr       */
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
	while (i < n && !pthread_mutex_init(&mtab[i], NULL))
	{
		i++;
	}
	if (i < n)
		return (err_minit);
	else
		return (err_none);
}

static void	t_forktab_init(t_all *all, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		all->ftab[i].mutex = &all->mutex[i];
		i++;
	}
}

t_error	t_all_init(t_all *all, int ac, char **av)
{
	all->error = err_none;
	all->av = parse_args(all, ac, av);
	if (all->error)
	{
		return (all->error);
	}
	all->mutex = ft_calloc(*(all->av[nbr]), sizeof(pthread_mutex_t));
	if (!all->mutex)
	{
		t_error_set(&all->error, err_malloc);
		return (all->error);
	}
	all->ftab = ft_calloc(*(all->av[nbr]), sizeof(t_fork));
	if (!all->ftab)
	{
		t_error_set(&all->error, err_malloc);
		return (all->error);
	}
	if (mutextab_init(all->mutex, *(all->av[nbr]))
		|| pthread_mutex_init(&all->out_m, NULL)
		|| pthread_mutex_init(&all->stop_m, NULL))
	{
		t_error_set(&all->error, err_minit);
		return (all->error);
	}
	t_forktab_init(all, *(all->av[nbr]));
	all->philo = t_philotab_init(all);
	if (!all->philo)
		return (all->error);
	all->stop = 0;
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
	if (all->ftab)
		free(all->ftab);
	if (all->philo)
		free(all->philo);
	if (all->av)
		size_tptrtab_free(all->av);
	pthread_mutex_destroy(&all->out_m);
}

void	print_error(t_error error)
{
	if (error)
		ft_putstr_fd("error ", 2);
	if (error == err_malloc)
		ft_putstr_fd("malloc\n", 2);
	else if (error == err_invalid_arg)
		ft_putstr_fd("invalid argument\n", 2);
	else if (error == err_thcreate)
		ft_putstr_fd("thread create\n", 2);
	else if (error == err_thjoin)
		ft_putstr_fd("thread join\n", 2);
	else if (error == err_minit)
		ft_putstr_fd("mutex init\n", 2);
	else if (error == err_mdestroy)
		ft_putstr_fd("mutex destroy\n", 2);
	else if (error == err_mlock)
		ft_putstr_fd("mutex lock\n", 2);
	else if (error == err_munlock)
		ft_putstr_fd("mutex unlock\n", 2);
}