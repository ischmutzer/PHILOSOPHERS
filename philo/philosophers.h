/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:56:58 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/17 20:15:56 by ischmutz         ###   ########.fr       */
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

# ifndef MAX_COUNT
#  define MAX_COUNT 201 // I think philo_count doesnt work, so i might need to allocate unnecesarilly large array
# endif

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
	int				is_eating;

	int				*start;
	int				last_meal;

	int				x_2_die; //how long to die
	int				x_2_eat; //how long to eat
	int				x_2_sleep; //how long to sleep
	int				num_meals; //how many meals to eat

	int				num_philo; //how many philos
	int				*dead_philo; //death flag
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;

	pthread_mutex_t	death_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;

	int				flag;
	int				start;
	int				philo_count;

}	t_data;

//philo_helpers.c
int		philo_atoi(const char *str);
int		check_whether_valid_input(int argc, char **args);
int		ft_get_time(void);
void 	ft_usleep(t_philo *philo, int time);
void	ft_bzero(void *s, size_t n);
void    lock_n_print(t_philo *philo, int id, char *msg);
int	    lock_death(t_philo *philo);
void    lock_meal(t_philo *philo, int mode);
void    cleanup_philos(t_data *data, int index);

//struct_init.c
void	data_init(t_data *data, t_philo *philos);
void	forks_init(pthread_mutex_t *forks, int philo_count);
void	philos_init(t_data *data, pthread_mutex_t *forks, t_philo *philos, char **argv);

#endif