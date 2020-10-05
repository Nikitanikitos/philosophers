/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 14:00:11 by imicah            #+#    #+#             */
/*   Updated: 2020/10/01 14:00:12 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

void	ft_putendl_fd(char *s, int fd)
{
	const int	buff = ft_strlen(s);

	if (buff)
		write(fd, &(*s), buff);
	write(fd, "\n", 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int		ft_strlen(const char *str)
{
	const char	*str_copy = str;

	while (*str)
		str++;
	return ((int)(str - str_copy));
}
