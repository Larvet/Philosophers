/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_proto.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:26:50 by marvin            #+#    #+#             */
/*   Updated: 2024/06/10 17:26:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PROTO_H
# define PHILO_PROTO_H

/* 00_t_all.c */
void	*t_error_set(t_all *all, t_error error);
int		t_all_init(t_all *all, int ac, char **av);
void	t_all_destroy(t_all *all);
void	t_all_print(t_all *all);

/* 01_t_philo.c */
void	t_philo_init(t_all *all, t_philo *p, size_t i);
void	t_philotab_print(t_philo *p);
t_philo	*t_philotab_init(t_all *all);

/* 02_t_philo_thread.c */
void	*t_philotab_thcreate(t_philo *p, size_t n);
void	*t_philotab_thjoin(t_philo *p, size_t n);

/* check_format.c */
int		ft_isdigit(int c);
int		isonly_digit(char *str);
int		check_format(char **av);

/* parsing.c */
int		ft_isspace(int c);
size_t	*ft_atosize_t(char *str);
size_t	**parse_args(t_all *all, int ac, char **av);

/* size_ttab_utils.c */
void	size_tptrtab_free(size_t **tab);
//size_t	*size_ttab_convert(size_t **tab, int n); //
void	size_tptrtab_print(size_t **tab);

#endif