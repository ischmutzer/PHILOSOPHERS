/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:04:45 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/29 15:15:22 by ischmutz         ###   ########.fr       */
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

int   pickup_forks(int counter, t_philo *philo)
{
    if (counter == 0)
    {
        if (philo->philo_id % 2 == 0)
        {
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
			return (0);
		}
        else
            if (ft_usleep(philo, (philo->x_2_eat - 0.05)) == 1)
				return (1);
	}
	if (philo->philo_id % 2 == 0) 
	{
		pthread_mutex_lock(philo->left_fork);
		usleep(20);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	return (0);
}

void	*lone_philo(void *arg)
{
	t_philo *philo = (t_philo*)arg;

	while (1)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		lock_n_print(philo, philo->philo_id, "has taken a fork");
		lock_n_print(philo, philo->philo_id, "has taken a fork");
		philo_is_eating(philo);
		lock_n_print(philo, philo->philo_id, "is eating");
		ft_usleep(philo, philo->x_2_eat);
		philo_finished_eating(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		lock_n_print(philo, philo->philo_id, "is sleeping");
		ft_usleep(philo, philo->x_2_sleep);
		lock_n_print(philo, philo->philo_id, "is thinking");
	}
}

void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo*)arg;
	int count = 0;

	while (1)
	{
		if (lock_death(philo) == 1)
			return (NULL);
		if (pickup_forks(count, philo) == 1)
			return (NULL);
		lock_n_print(philo, philo->philo_id, "has taken a fork");
		lock_n_print(philo, philo->philo_id, "has taken a fork");
		philo_is_eating(philo);
		lock_n_print(philo, philo->philo_id, "is eating");
		if (ft_usleep(philo, philo->x_2_eat) == 1)
			return (NULL);
		philo_finished_eating(philo);
		if (philo->philo_id % 2 != 0) 
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		else
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		lock_n_print(philo, philo->philo_id, "is sleeping");
		if (ft_usleep(philo, philo->x_2_sleep) == 1)
			return (NULL);
		lock_n_print(philo, philo->philo_id, "is thinking");
		usleep(50);
		count++;
	}
}

void	*monitoring(void *arg)
{
	t_data	*data = (t_data*)arg;
	int		i;
	int		counter;

	while (1)
	{
		i = 0;
		counter = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_lock(&data->meal_lock);
			if ((ft_get_time() - data->philos[i].last_meal) > (size_t)data->philos[i].x_2_die)
			{
				change_flag(data);
				lock_print(data, data->philos[i].philo_id, "died");
				pthread_mutex_unlock(&data->meal_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&data->meal_lock);
			if (data->num_meals != -1)
			{
				pthread_mutex_lock(&data->meal_lock);
				if (data->philos[i].meals_eaten >= data->num_meals)
					counter++;
				pthread_mutex_unlock(&data->meal_lock);
				if (counter == data->philo_count)
				{
					change_flag(data);
					return (NULL);
				}
			}
			i++;
		}
		// REMOVE ITS ONLY FOR VALGRIND
		usleep(200);
	}
}

int	philo_creator(t_data *data)
{
	int			i;

	i = -1;
	data->start = ft_get_time();
	if (pthread_create(&data->monitor, NULL, monitoring, data))
		return (change_flag(data), cleanup_philos(data, i), 1);
	while (++i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_lock);
		data->philos[i].last_meal = data->start;
		pthread_mutex_unlock(&data->meal_lock);
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]))
			return (change_flag(data), cleanup_philos(data, i), 1);
	}
	cleanup_philos(data, -1);
	cleanup_philos(data, data->philo_count);
	return (0);
}


void	handle_one_philo(t_data *data)
{
	data->start = ft_get_time();
	if (pthread_create(&data->philos[0].thread, NULL, lone_philo, &data->philos[0]))
		return (change_flag(data), cleanup_philos(data, data->philo_count));
	cleanup_philos(data, data->philo_count);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philos;
	int				i;

	bzero(&data, sizeof(data));
	data.philo_count = philo_atoi(argv[1]);
	philos = (t_philo *)malloc(data.philo_count * sizeof(t_philo));
	if (!philos)
		return (printf("malloc failed\n"), 1);
	data.forks = malloc(sizeof(pthread_mutex_t) * data.philo_count);
	if (!data.forks)
		return(free(philos), printf("malloc failed\n"), 1);

	bzero(philos, sizeof(*philos));
	i = -1;
	if (check_whether_valid_input(argc, argv))
		return (1);
	data_init(&data, philos, argv);
	forks_init(&data, data.philo_count);
	philos_init(&data, philos, argv);
	if (data.philo_count == 1)
		handle_one_philo(&data);
	else
	 	philo_creator(&data);
	return (0);
}
