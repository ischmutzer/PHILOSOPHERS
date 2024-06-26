/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:17:53 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/31 13:22:09 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	init_all(t_data *data, t_philo *philos, char **argv)
{
	if (data_init(data, philos, argv))
		return (1);
	if (forks_init(data, data->philo_count))
		return (1);
	philos_init(data, philos, argv);
	return (0);
}

int	data_init(t_data *data, t_philo *philos, char **argv)
{
	if (argv[5])
		data->num_meals = philo_atoi(argv[5]);
	else
		data->num_meals = -1;
	data->philos = philos;
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (1);
	return (0);
}

int	forks_init(t_data *data, int philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count)
	{
		if (pthread_mutex_init(&(data->forks)[i], NULL) != 0)
			return (1);
	}
	return (0);
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
void	philos_init(t_data *data, t_philo *philos, char **argv)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		philos[i].philo_id = i;
		philos[i].meals_eaten = 0;
		philos[i].start = &data->start;
		philos[i].x_2_die = philo_atoi(argv[2]);
		philos[i].x_2_eat = philo_atoi(argv[3]);
		philos[i].x_2_sleep = philo_atoi(argv[4]);
		if (argv[5])
			philos[i].num_meals = philo_atoi(argv[5]);
		else
			philos[i].num_meals = -1;
		philos[i].num_philo = philo_atoi(argv[1]);
		philos[i].dead_philo = &data->flag;
		philos[i].left_fork = &(data->forks)[i];
		philos[i].right_fork = &(data->forks)[(i + 1) % philo_atoi(argv[1])];
		philos[i].print_lock = &data->print_lock;
		philos[i].death_lock = &data->death_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].last_meal = ft_get_time();
	}
}
