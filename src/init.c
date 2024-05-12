/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:33:05 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/12 16:42:26 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->nb_must_eat = -1;
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]);
	data->philo_must_eat = 0;
	if (data->nb_philo < 2 || data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60 || (ac == 6 && data->nb_must_eat < 1))
		return (printf("Error: Invalid arguments\n"), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (printf("Error: malloc failed\n"), 1);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	gettimeofday(&data->start, NULL);
	return (0);
}

int	init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (printf("Error: malloc failed\n"), 1);
	i = -1;
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
			return (printf("Error: pthread_create failed\n"), 1);
	}
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(philo[i].thread, NULL);
	return (0);
}
