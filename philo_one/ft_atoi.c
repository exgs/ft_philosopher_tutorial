/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:19:28 by yunslee           #+#    #+#             */
/*   Updated: 2021/03/08 21:21:33 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static int	ft_isblank(char c)
{
	if (c == ' ' || c == '\n' || c == '\r'
			|| c == '\v' || c == '\f' || c == '\t')
		return (1);
	return (0);
}

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	char		*s;
	long long	ret;
	long long	flag;

	s = (char *)str;
	ret = 0;
	flag = 1;
	while (ft_isblank(*s) && *s)
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			flag *= -1;
	while (ft_isdigit(*s))
	{
		ret = ret * 10 + *s - '0';
		if (ret < 0)
		{
			if (flag < 0)
				return (0);
			else
				return (-1);
		}
		s++;
	}
	return (ret * flag);
}
