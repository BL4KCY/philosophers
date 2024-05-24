/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:43:26 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/23 15:45:50 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)philo;
	if (p->id % 2)
		usleep(100);
	i = 0;
	while (i != p->data->nb_must_eat && !p->data->dead)
	{
		if (hold_fork(p))
			return (NULL);
		if (drop_fork(p, i))
			return (NULL);
		if (p->data->nb_must_eat != -1)
			++i;
	}
	return (NULL);
}
