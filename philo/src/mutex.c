/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:49:38 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/23 18:40:47 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	t_mutex_init(t_mutex *mutex)
{
	if (pthread_mutex_init(&mutex->mutex, NULL))
		return (1);
	mutex->locked = false;
	return (0);
}

int	t_mutex_lock(t_mutex *mutex)
{
	if (pthread_mutex_lock(&mutex->mutex))
		return (1);
	mutex->locked = true;
	return (0);
}

int	t_mutex_unlock(t_mutex *mutex)
{
	if (pthread_mutex_unlock(&mutex->mutex))
		return (1);
	mutex->locked = false;
	return (0);
}

int	t_mutex_trylock(t_mutex *mutex)
{
	if (mutex->locked)
		return (1);
	return (t_mutex_lock(mutex));
}

int	t_mutex_tryunlock(t_mutex *mutex)
{
	if (!mutex->locked)
		return (1);
	return (t_mutex_unlock(mutex));
}
