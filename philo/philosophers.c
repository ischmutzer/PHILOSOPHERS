/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:04:45 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/30 19:33:46 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/pthreadtypes.h>
//#include <cstdlib>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	ft_usleep(philo, philo->x_2_die);
	pthread_mutex_unlock(philo->left_fork);
	print_philos(philo, philo->philo_id, "died");
	return (NULL);
}

int	philo_creator(t_data *data)
{
	int	i;

	i = -1;
	data->start = ft_get_time();
	if (pthread_create(&data->monitor, NULL, monitoring, data))
		return (change_flag(data), cleanup_philos(data, i), 1);
	while (++i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_lock);
		data->philos[i].last_meal = data->start;
		pthread_mutex_unlock(&data->meal_lock);
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]))
			return (change_flag(data), cleanup_philos(data, i), 1);
	}
	cleanup_philos(data, -1);
	cleanup_philos(data, data->philo_count);
	return (0);
}

void	handle_one_philo(t_data *data)
{
	data->start = ft_get_time();
	if (pthread_create(&data->philos[0].thread, NULL,
			lone_philo, &data->philos[0]))
		return (change_flag(data), cleanup_philos(data, data->philo_count));
	cleanup_philos(data, data->philo_count);
}

int	init_all(t_data *data, t_philo *philos, char **argv)
{
	if (data_init(data, philos, argv))
		return (1);
	if (forks_init(data, data->philo_count))
		return (1);
	philos_init(data, philos, argv);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (check_whether_valid_input(argc, argv))
		return (1);
	memset(&data, 0, sizeof(data));
	data.philo_count = philo_atoi(argv[1]);
	philos = (t_philo *)malloc(data.philo_count * sizeof(t_philo));
	if (!philos)
		return (printf("malloc failed\n"), 1);
	data.forks = malloc(sizeof(pthread_mutex_t) * data.philo_count);
	if (!data.forks)
		return (free(philos), printf("malloc failed\n"), 1);
	memset(philos, 0, sizeof(*philos));
	if (init_all(&data, philos, argv))
		return (printf("Failure at initialization\n"), 1);
	// data_init(&data, philos, argv);
	// forks_init(&data, data.philo_count);
	// philos_init(&data, philos, argv);
	if (data.philo_count == 1)
		handle_one_philo(&data);
	else
		philo_creator(&data);
	return (0);
}
