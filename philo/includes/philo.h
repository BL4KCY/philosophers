/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:05:51 by melfersi          #+#    #+#             */
/*   Updated: 2024/02/21 09:09:26 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

typedef struct s_philo
{
	int				id;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				*forks;
	int				*eat_count;
	int				*last_meal;
	int				*is_eating;
	int				*is_dead;
	pthread_t		*philo;
	pthread_t		*monitor;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*fork;
}					t_philo;


#endif
