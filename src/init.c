/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:33:05 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/20 18:44:44 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int ac, char **av)
{
	int	i;

	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->nb_must_eat = -1;
	data->dead = false;
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]);
	data->philo_must_eat = 0;
	if (!check_args(data))
		return (1);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	return (gettimeofday(&data->start, NULL), 0);
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
	return (start_philo(philo, data));
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

int	start_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (write(2, "Error: pthread_create failed\n", 30), 1);
	if (pthread_create(&data->death_thread, NULL, check_death, philo))
		return (write(2, "Error: pthread_create failed\n", 30), 1);
	if (pthread_join(data->death_thread, NULL))
		return (write(2, "Error: pthread_join failed\n", 27), 1);
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(philo[i].thread, NULL);
	return (0);
}
