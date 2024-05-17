/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:17:53 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/17 19:34:26 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	data_init(t_data *data, t_philo *philos)
{
	//t_philo	*philos[philo_count];
	//int		i;

	data->flag = 0;
	//i = -1;
	// while (++i <= philo_count)
	// 	philos[i] = (t_philo *)malloc(sizeof(t_philo));
	
	//bzero(philos, sizeof(philos));
	//printf("nphilo: %d", philos[0]->num_philo);
	data->philos = philos;
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}

void	forks_init(pthread_mutex_t *forks, int philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count)
		pthread_mutex_init(&forks[i], NULL);
}

//Modulo:
// Philosopher 0: (0 + 1) % 5 = 1. So, the right fork for philosopher 0
//  is at index 1 in the forks array.
// Philosopher 1: (1 + 1) % 5 = 2. So, the right fork for philosopher 1
//  is at index 2 in the forks array.
// Philosopher 2: (2 + 1) % 5 = 3. So, the right fork for philosopher 2
//  is at index 3 in the forks array.
// Philosopher 3: (3 + 1) % 5 = 4. So, the right fork for philosopher 3
//  is at index 4 in the forks array.
// Philosopher 4: (4 + 1) % 5 = 0. So, the right fork for philosopher 4
//  is at index 0 in the forks array.

//This setup simulates a circular table where each philosopher is sitting 
//between two forks and can reach the fork to their immediate left and right.
//The modulus operator (%) is used to create the circular effect,
//where the last philosopher's right fork is the first fork in the array.
void	philos_init(t_data *data, pthread_mutex_t *forks, t_philo *philos, char **argv)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		philos[i].philo_id = i;
		philos[i].meals_eaten = 0;
		philos[i].is_eating = 0;
		philos[i].start = &data->start;
		philos[i].last_meal = ft_get_time();
		philos[i].x_2_die = philo_atoi(argv[2]);
		philos[i].x_2_eat = philo_atoi(argv[3]);
		philos[i].x_2_sleep = philo_atoi(argv[4]);
		if (argv[5])
			philos[i].num_meals = philo_atoi(argv[5]);
		else
			philos[i].num_meals = -1;
		philos[i].num_philo = philo_atoi(argv[1]);
		philos[i].dead_philo = &data->flag;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % philo_atoi(argv[1])];
		philos[i].print_lock = &data->print_lock;
		philos[i].death_lock = &data->death_lock;
		philos[i].meal_lock = &data->meal_lock;
	}
}
