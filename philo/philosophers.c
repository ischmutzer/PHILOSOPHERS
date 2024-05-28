/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:04:45 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/28 19:45:45 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/pthreadtypes.h>
//#include <cstdlib>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
		lock_n_print(philo, philo->philo_id, "has taken a fork", 1);
		lock_n_print(philo, philo->philo_id, "has taken a fork", 1);
		philo_is_eating(philo);
		lock_n_print(philo, philo->philo_id, "is eating", 1);
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
		lock_n_print(philo, philo->philo_id, "is sleeping", 1);
		if (ft_usleep(philo, philo->x_2_sleep) == 1)
			return (NULL);
		lock_n_print(philo, philo->philo_id, "is thinking", 1);
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
			if ((ft_get_time() - data->philos[i].last_meal) > data->philos[i].x_2_die)
			{
				change_flag(data);
				lock_n_print(&data->philos[i], data->philos[i].philo_id, "died", 0);
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
	}
}

int	philo_creator(t_data *data)
{
	int			i;

	i = -1;
	//pthread_mutex_lock(&data->death_lock);
	// if (data->flag == 1) //does this do anything?
	// {
	// 	pthread_mutex_lock(&data->death_lock);
	// 	pthread_mutex_lock(&data->print_lock);
	// 	printf("Philo is dead\n");
	// 	pthread_mutex_unlock(&data->print_lock);
	// 	return (1);
	// }
	//pthread_mutex_unlock(&data->death_lock);
	if (pthread_create(&data->monitor, NULL, monitoring, data))
		return (printf("monitor failed\n"), cleanup_philos(data, i), 1);
	data->start = ft_get_time();
	while (++i < data->philo_count)
	{
		data->philos[i].last_meal = data->start;
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]))
			return (printf("philos failed\n"),cleanup_philos(data, i), 1);
	}
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			data->flag = 1;
		cleanup_philos(data, i);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philos;
	pthread_mutex_t	forks[MAX_COUNT];
	int				i;

	bzero(&data, sizeof(data));
	data.philo_count = philo_atoi(argv[1]);
	philos = (t_philo *)malloc(data.philo_count * sizeof(t_philo));
	bzero(philos, sizeof(*philos));
	i = -1;
	if (check_whether_valid_input(argc, argv))
		return (1);
	data_init(&data, philos, argv);
	forks_init(forks, data.philo_count);
	philos_init(&data, forks, philos, argv);
	if (philo_creator(&data))
		return (printf("im here\n"), 0);
	return (0);
}
