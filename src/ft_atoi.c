/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:59:07 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/20 18:50:56 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ssize_t	ft_atoi(const char *str)
{
	ssize_t		nb;
	int			sign;

	nb = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (nb * 10 + *str - '0' < nb)
			return (-1);
		nb = nb * 10 + *str++ - '0';
	}
	if ((sign == 1 && sign * nb < 0) || (sign == -1 && sign * nb > 0))
		return (-1);
	return (nb * sign);
}
