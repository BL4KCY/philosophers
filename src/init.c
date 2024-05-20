/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:33:05 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/20 09:56:12 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	data->nb_must_eat = -1;
	data->dead = false;
	if (ac == 6)
		data->nb_must_eat = atoi(av[5]);
	data->philo_must_eat = 0;
	if (!check_args(data))
		return (1);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	for (int i = 0; i < data->nb_philo; i++)
		pthread_mutex_init(&data->forks[i], NULL);
	gettimeofday(&data->start, NULL);
	return (0);
}

int	init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	data->philo = philo;
	while (++i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
	}
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (write(2, "Error: pthread_create failed\n", 30), 1);
	}
	if (pthread_create(&data->death_thread, NULL, check_death, philo))
		return (write(2, "Error: pthread_create failed\n", 30), 1);
	if (pthread_join(data->death_thread, NULL))
		return (write(2, "Error: pthread_join failed\n", 27), 1);
	for (int i = 0; i < data->nb_philo; i++)
		pthread_join(philo[i].thread, NULL);
	return (0);
}

bool	check_args(t_data *data)
{
	if (data->nb_philo < 1 || data->nb_philo > 200)
		return (false);
	if (data->time_to_die < 60)
		return (false);
	if (data->time_to_eat < 60)
		return (false);
	if (data->time_to_sleep < 60)
		return (false);
	if (data->nb_must_eat != -1 && data->nb_must_eat < 1)
		return (false);
	return (true);
}
