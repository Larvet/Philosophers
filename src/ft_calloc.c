/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <locharve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:21:37 by locharve          #+#    #+#             */
/*   Updated: 2024/07/16 15:26:20 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
	return ;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;

	ptr = NULL;
	if ((nmemb > 65535 && size > 65535) || nmemb * size > 2147483647)
		return (ptr);
	ptr = (unsigned char *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return ((void *)ptr);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0 || s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
	return ;
}