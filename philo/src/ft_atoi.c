/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:59:07 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/21 21:54:02 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ssize_t	ft_atoi(const char *str)
{
	ssize_t		nb;
	int			sign;

	nb = 0;
	sign = 1;
	if (is_number((char *)str) == false)
		return (-2);
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		if (nb * 10 + *str - '0' < nb)
			return (-2);
		nb = nb * 10 + *str++ - '0';
	}
	if ((sign == 1 && sign * nb < 0) || (sign == -1 && sign * nb > 0))
		return (-2);
	if (nb * sign == -1)
		return (-2);
	return (nb * sign);
}

bool	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}
