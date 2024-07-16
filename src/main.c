/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:05:42 by locharve          #+#    #+#             */
/*   Updated: 2024/06/24 15:59:52 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc > 6)
		ft_putstr_fd("Too many arguments.\n", 2);
	else if (argc >= 5)
	{
		if (check_format(argv + 1))
		{
			if (t_all_init(&all, argc - 1, argv + 1))
				print_error(all.error);
			else
			{
				if (!t_philotab_thcreate(all.philo, *(all.av[nbr])))
					t_philotab_thjoin(all.philo, *(all.av[nbr]));
				t_all_destroy(&all);
			}
		}
		else
			ft_putstr_fd("Invalid argument(s).\n", 2);
	}
	else
		ft_putstr_fd("Too few arguments.\n", 2);
	return (0);
}
