/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:43:26 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/15 09:55:03 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)philo;
	i = 0;
	while (i != p->data->nb_must_eat && !p->data->dead)
	{
		get_fork(p);
		drop_fork(p);
		if (p->data->nb_must_eat != -1)
			++i;
	}
	return (NULL);
}
