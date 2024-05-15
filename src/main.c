/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:19:55 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/14 18:17:10 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int main(int ac, char **av)
{
	t_data data;

	if (ac != 5 && ac != 6 && av)
		return (printf("usage: ./philo <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep> [nb_must_eat]\n"), 0);
	if (init_data(&data, ac, av))
		return (1);
	if (init_philo(&data))
		return (1);
	return (0);
}
