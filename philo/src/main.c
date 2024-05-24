/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:19:55 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/23 16:07:53 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_msg(t_data *data, int id, char *msg)
{
	t_mutex_lock(&data->print);
	t_mutex_lock(&data->death);
	if (!data->dead || !strcmp(msg, "died"))
		printf("%ld %d %s\n", get_time(data), id, msg);
	if (!strcmp(msg, "died"))
	{
		t_mutex_unlock(&data->print);
		t_mutex_unlock(&data->death);
		return (1);
	}
	t_mutex_unlock(&data->print);
	t_mutex_unlock(&data->death);
	return (0);
}

int	check_finish(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->data->nb_philo)
		if (!(p->data->philo[i++].finish_meal))
			return (0);
	return (2);
}

int	main(int ac, char **av)
{
	t_data	data;

	data.philo = NULL;
	data.forks = NULL;
	if (ac != 5 && ac != 6 && av)
		return (1);
	if (init_data(&data, ac, av))
		return (1);
	if (init_philo(&data))
		return (1);
	free(data.forks);
	free(data.philo);
	return (0);
}
