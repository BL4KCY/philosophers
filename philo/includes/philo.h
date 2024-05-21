/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:19:15 by melfersi          #+#    #+#             */
/*   Updated: 2024/05/21 18:53:19 by melfersi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

//_____________________Structures_____________________//

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				philo_must_eat;
	bool			dead;
	pthread_t		death_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	struct timeval	start;
	struct s_philo	*philo;
}				t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal;
	bool			finish_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}				t_philo;

//_____________________Prototypes_____________________//

int		init_data(t_data *data, int ac, char **av);
int		init_philo(t_data *data);
void	*routine(void *philo);
long	get_time(t_data *data);
int		print_msg(t_data *data, int id, char *msg);
void	*check_death(void *philo);
int		hold_fork(t_philo *p);
int		drop_fork(t_philo *p, int i);
void	ft_usleep(long time);
bool	check_args(t_data *data);
ssize_t	ft_atoi(const char *str);
int		start_philo(t_philo *philo, t_data *data);
int		check_finish(t_philo *p);

#endif
