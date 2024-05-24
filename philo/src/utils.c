/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:07:45 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/23 18:47:56 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_data *data)
{
	struct timeval	current;
	int				data_time;
	int				current_time;

	gettimeofday(&current, NULL);
	current_time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	data_time = (data->start.tv_sec * 1000) + (data->start.tv_usec / 1000);
	return (current_time - data_time);
}

void	*check_death(void *data)
{
	t_data	*d;
	int		i;

	d = (t_data *)data;
	while (1)
	{
		i = -1;
		while (++i < d->nb_philo)
		{
			if (get_time(d) - d->philo[i].last_meal > d->time_to_die)
			{
				d->dead = true;
				print_msg(d, i + 1, "died");
				return (t_mutex_tryunlock(&d->forks[0]), NULL);
			}
			if (d->philo[i].finish_meal)
				if (check_finish(&d->philo[i]))
					return (t_mutex_tryunlock(&d->forks[0]), NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	hold_fork(t_philo *p)
{
	if (p->id % 2)
		t_mutex_lock(p->right_fork);
	else
		t_mutex_lock(p->left_fork);
	if (print_msg(p->data->philo->data, p->id, "has taken a fork"))
		return (1);
	if (p->id % 2)
		t_mutex_lock(p->left_fork);
	else
		t_mutex_lock(p->right_fork);
	if (print_msg(p->data->philo->data, p->id, "has taken a fork"))
		return (1);
	return (0);
}

int	drop_fork(t_philo *p, int i)
{
	p->last_meal = get_time(p->data);
	if (print_msg(p->data->philo->data, p->id, "is eating"))
		return (1);
	ft_usleep(p->data->time_to_eat);
	t_mutex_unlock(p->left_fork);
	t_mutex_unlock(p->right_fork);
	if (i + 1 == p->data->nb_must_eat)
		return (p->finish_meal = true, 1);
	if (print_msg(p->data->philo->data, p->id, "is sleeping"))
		return (1);
	ft_usleep(p->data->time_to_sleep);
	if (print_msg(p->data->philo->data, p->id, "is thinking"))
		return (1);
	return (0);
}

void	ft_usleep(long ms)
{
	struct timeval	current;
	struct timeval	start;
	int				start_time;
	int				current_time;
	long			sleep_time;

	sleep_time = 1;
	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&current, NULL);
		start_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
		current_time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
		if (current_time - start_time >= ms)
			break ;
		usleep(sleep_time);
	}
}
