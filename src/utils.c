/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:07:45 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/20 15:58:24 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long	get_time(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - (data->start.tv_sec * 1000) - (data->start.tv_usec / 1000));
}

int	print_msg(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data->death);
	pthread_mutex_lock(&data->print);
	if (!data->dead || !strcmp(msg, "died"))
		printf("%ld %d %s\n", get_time(data), id, msg);
	if (!strcmp(msg, "died"))
	{
		pthread_mutex_unlock(&data->print);
		pthread_mutex_unlock(&data->death);
		return (1);
	}
	pthread_mutex_unlock(&data->print);
	pthread_mutex_unlock(&data->death);
	return (0);
}

void	*check_death(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		pthread_mutex_lock(&p->data->death);
		if (get_time(p->data) - p->last_meal > p->data->time_to_die)
		{
			for (int i = 0; i < p->data->nb_philo; i++)
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

int		get_fork(t_philo *p)
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
	struct timeval	time;
	struct timeval	start;
	long			sleep_time;

	sleep_time = 1;
	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&time, NULL);
		if (((time.tv_sec * 1000) + (time.tv_usec / 1000) - (start.tv_sec * 1000) - (start.tv_usec / 1000)) >= ms)
			break ;
		usleep(sleep_time);
	}
}
