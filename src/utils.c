/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:07:45 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/15 18:24:31 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long	get_time(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - (data->start.tv_sec * 1000) - (data->start.tv_usec / 1000));
}

void	print_msg(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data->print);
	if (!data->dead || !strcmp(msg, "died"))
		printf("%ld %d %s\n", get_time(data), id, msg);
	pthread_mutex_unlock(&data->print);
}

void	*check_death(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		if (get_time(p->data) - p->last_meal > p->data->time_to_die)
		{
			p->data->dead = true;
			print_msg(p->data, p->id, "died");
			return (NULL);
		}
	}
	return (NULL);
}

void	get_fork(t_philo *p)
{
	if (p->id % 2)
		pthread_mutex_lock(p->right_fork);
	else
		pthread_mutex_lock(p->left_fork);
	print_msg(p->data, p->id, "has taken a fork");
	if (p->id % 2)
		pthread_mutex_lock(p->left_fork);
	else
		pthread_mutex_lock(p->right_fork);
	print_msg(p->data, p->id, "has taken a fork");
}

void	drop_fork(t_philo *p)
{
	p->last_meal = get_time(p->data);
	print_msg(p->data, p->id, "is eating");
	ft_usleep(p->data->time_to_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	print_msg(p->data, p->id, "is sleeping");
	ft_usleep(p->data->time_to_sleep);
	print_msg(p->data, p->id, "is thinking");
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
