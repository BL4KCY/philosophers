/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:07:45 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/21 06:55:58 by melfersi         ###   ########.fr       */
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

void	*check_death(void *philo)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)philo;
	while (1)
	{
		pthread_mutex_lock(&p->data->death);
		if (get_time(p->data) - p->last_meal > p->data->time_to_die)
		{
			i = -1;
			while (++i < p->data->nb_philo)
				p->data->philo[i].data->dead = true;
			pthread_mutex_unlock(&p->data->death);
			print_msg(p->data, p->id, "died");
			ft_usleep(100);
			return (NULL);
		}
		pthread_mutex_unlock(&p->data->death);
	}
	return (NULL);
}

int	hold_fork(t_philo *p)
{
	if (p->id % 2)
		pthread_mutex_lock(p->right_fork);
	else
		pthread_mutex_lock(p->left_fork);
	if (print_msg(p->data->philo->data, p->id, "has taken a fork"))
		return (1);
	if (p->id % 2)
		pthread_mutex_lock(p->left_fork);
	else
		pthread_mutex_lock(p->right_fork);
	if (print_msg(p->data->philo->data, p->id, "has taken a fork"))
		return (1);
	return (0);
}

int	drop_fork(t_philo *p)
{
	pthread_mutex_lock(&p->data->death);
	p->last_meal = get_time(p->data);
	pthread_mutex_unlock(&p->data->death);
	if (print_msg(p->data->philo->data, p->id, "is eating"))
		return (1);
	ft_usleep(p->data->time_to_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
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
