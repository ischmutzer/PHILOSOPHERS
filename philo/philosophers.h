/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:56:58 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/29 19:52:40 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

//x = time in ms
typedef struct s_philo
{
	pthread_t		thread;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*meal_lock;

	int				philo_id;
	int				meals_eaten;
	size_t			*start;
	size_t			last_meal;

	int				x_2_die; //how long to die
	int				x_2_eat; //how long to eat
	int				x_2_sleep; //how long to sleep
	int				num_meals; //how many meals to eat
	int				num_philo; //how many philos
	int				*dead_philo; //death flag
}	t_philo;

typedef struct s_data
{
	t_philo				*philos;

	pthread_t			monitor;

	pthread_mutex_t		death_lock;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		*forks;

	int					flag;
	size_t				start;
	int					philo_count;
	int					num_meals;

}	t_data;

//HELPER_FUNCTIONS ->checker_atoi.c
int		philo_atoi(const char *str);
int		check_whether_valid_input(int argc, char **args);

//HELPER_FUCNTIONS ->clean_up.c
void	destroy_mutexes(t_data *data);
void	cleanup_philos(t_data *data, int index);

//HELPER_FUNCTIONS ->helper_functions.c
size_t	ft_get_time(void);
int		ft_usleep(t_philo *philo, int time);
void	ft_bzero(void *s, size_t n);

//HELPER_FUCNTIONS ->monitor_helper.c
void	print_monitor(t_data *data, int id, char *msg);
void	change_flag(t_data *data);

//HELPER_FUNCTIONS ->routine_helper
void	print_philos(t_philo *philo, int id, char *msg);
int		lock_death(t_philo *philo);
void	philo_is_eating(t_philo *philo);
void	philo_finished_eating(t_philo *philo);

//struct_init.c
void	data_init(t_data *data, t_philo *philos, char **argv);
void	forks_init(t_data *data, int philo_count);
void	philos_init(t_data *data, t_philo *philos, char **argv);

//PHILOS ->routine.c
int		pickup_forks(int counter, t_philo *philo);
void	drop_forks(t_philo *philo);
void	*philo_routine(void *arg);

//MONITOR ->monitor.c
void	*monitoring(void *arg);

int		init_n_malloc_struct(t_data *data, t_philo **philos, char **argv);

#endif