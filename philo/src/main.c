/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:19:55 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/20 23:14:10 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg(void)
{
	printf("usage: ./philo <nb_philo> <time_to_die> %s",
		"<time_to_eat> <time_to_sleep> [nb_must_eat]\n");
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

int	main(int ac, char **av)
{
	t_data	data;

	data.philo = NULL;
	data.forks = NULL;
	if (ac != 5 && ac != 6 && av)
		return (error_msg(), 1);
	if (init_data(&data, ac, av))
		return (1);
	if (init_philo(&data))
		return (1);
	free(data.forks);
	free(data.philo);
	return (0);
}
