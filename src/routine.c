/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:43:26 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/20 10:11:50 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)philo;
	i = 0;
	pthread_mutex_lock(&p->data->death);
	while (i != p->data->nb_must_eat && !p->data->dead)
	{
		pthread_mutex_unlock(&p->data->death);
		if (get_fork(p))
			return (NULL);
		if (drop_fork(p))
			return (NULL);
		if (p->data->nb_must_eat != -1)
			++i;
		pthread_mutex_lock(&p->data->death);
	}
	pthread_mutex_unlock(&p->data->death);
	return (NULL);
}
