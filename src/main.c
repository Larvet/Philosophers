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
		printf("Too many arguments.\n");
	else if (argc >= 5)
	{
		if (check_format(argv + 1))
		{
			t_all_init(&all, argc - 1, argv + 1);
			// lancer routines
			// t_all_print(&all);
			t_all_destroy(&all);
		}
		else
			printf("Invalid argument(s).\n");
	}
	else
		printf("Too few arguments.\n");
	return (0);
}
