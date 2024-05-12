/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:19:55 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/12 16:37:27 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int main(int ac, char **av)
{
	t_data data;

	if (ac != 5 && ac != 6 && av)
		return (printf("Error: Wrong number of arguments\n"), 1);
	if (init_data(&data, ac, av))
		return (1);
	if (init_philo(&data))
		return (1);
}
