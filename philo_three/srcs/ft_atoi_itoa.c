/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 02:30:36 by imicah            #+#    #+#             */
/*   Updated: 2020/05/05 18:07:05 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

char		ft_isdigit(char c)
{
	return ('0' <= c && c <= '9');
}

static int	ft_isspace(char c)
{
	return ((c == '\n' || c == '\t' || c == '\r' ||
			c == '\v' || c == '\f' || c == ' '));
}

int			ft_atoi(char *nptr)
{
	int		result;
	char	pos_or_neg;

	result = 0;
	pos_or_neg = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*(nptr++) == '-')
			pos_or_neg = -1;
	while (*nptr >= '0' && *nptr <= '9')
		result = result * 10 + (*(nptr++) - '0');
	result *= pos_or_neg;
	return (result);
}

static int	ft_len(long int n)
{
	unsigned char	i;

	i = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
		i++;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char		*ft_itoa(long int n)
{
	int				i;
	char			*result;
	char			pos_or_neg;

	i = ft_len(n);
	pos_or_neg = 1;
	if (!(result = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	result[i--] = '\0';
	if (n == 0)
		result[i--] = '0';
	else if (n < 0)
	{
		result[0] = '-';
		pos_or_neg = -1;
	}
	while (n)
	{
		result[i--] = ((n % 10) * pos_or_neg) + 48;
		n /= 10;
	}
	return (result);
}
