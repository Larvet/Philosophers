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
void	*t_error_set(t_error *to_set, t_error error);
unsigned long	get_timestamp(void);
t_error	t_all_init(t_all *all, int ac, char **av);
void	t_all_destroy(t_all *all);
void	t_all_print(t_all *all);
void	print_error(t_error error);

/* 01_t_philo.c */
t_error	t_fork_init(t_all *all, t_fork *f, size_t i);
t_error	t_philo_init(t_all *all, t_philo *p, size_t i);
void	t_philotab_print(t_philo *p);
t_error	t_philotab_free(t_philo *p, size_t n);
t_philo	*t_philotab_init(t_all *all);
char	*get_state_str(t_state state);
size_t	t_philo_set_state(t_philo *p, t_state state);
void	print_state(pthread_mutex_t *m, unsigned long time, size_t i, char *str);

/* 02_t_philo_thread.c */
t_error	t_philotab_thcreate(t_philo *p, size_t n);
t_error	t_philotab_thjoin(t_philo *p, size_t n);

/* check_format.c */
int		ft_isdigit(int c);
int		isonly_digit(char *str);
int		check_format(char **av);

/* parsing.c */
int		ft_isspace(int c);
size_t	*ft_atosize_t(char *str);
size_t	**parse_args(t_all *all, int ac, char **av);

/* ft_calloc.c */
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

/* routine.c */
int	is_there_dead_philo(t_philo *ptab, size_t n);
void	*routine(void *arg);

/* size_ttab_utils.c */
void	size_tptrtab_free(size_t **tab);
//size_t	*size_ttab_convert(size_t **tab, int n); //
void	size_tptrtab_print(size_t **tab);

/* t_philo_action.c */
int	t_philo_wait(size_t arg, size_t to_die, size_t last_meal_time); // rename ?
int	t_philo_eat(t_philo *p);
int	t_philo_sleep(t_philo *p);

/* t_philo_lock_mutex.c
t_error	t_philo_lock_mutex(t_philo *p, t_fork *f);
t_error	t_philo_unlock_mutex(t_philo *p, t_fork *f);
t_error	t_philo_odd_or_even_mutex(t_philo *p, t_error f_m(t_philo *, t_fork *), int b);
*/

/* t_philo_mutex.c */
// int	t_philo_mutex_lock(t_philo *p, t_fork *f);
int	t_philo_mutex_lock_hub(t_philo *p);
void	t_philo_unlock_hub(t_philo *p);

#endif