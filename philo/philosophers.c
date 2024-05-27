/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:04:45 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/27 18:58:31 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/pthreadtypes.h>
//#include <cstdlib>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo*)arg;
	int count = 0;
	
	
	while (1)
	{	
		// hardcode first iteration of hte loop so that only odd or even eat
		// and the other group usleeps for time to eat - 50 us
		separate_group(count, philo);
		if (lock_death(philo) == 1)
			return (NULL);
		if (philo->philo_id % 2 == 0)
			pthread_mutex_lock(philo->left_fork);
		else
			pthread_mutex_lock(philo->right_fork);
		if (philo->philo_id % 2 == 0)
			pthread_mutex_lock(philo->right_fork);
		else
			pthread_mutex_lock(philo->left_fork);
		lock_n_print(philo, philo->philo_id, "has taken a fork");
		lock_n_print(philo, philo->philo_id, "has taken a fork");
		lock_meal(philo, 1);
		lock_n_print(philo, philo->philo_id, "is eating");
		ft_usleep(philo, philo->x_2_eat);
		lock_meal(philo, 2);
		lock_meal(philo, 3);
		lock_meal(philo, 0);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		lock_n_print(philo, philo->philo_id, "is sleeping");
		ft_usleep(philo, philo->x_2_sleep);
		lock_n_print(philo, philo->philo_id, "is thinking");
		//ft_usleep(philo, (philo->x_2_die - (philo->x_2_die - 5)));
		//add tiny usleep to handle case where they pick up fork before hungry philos
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
		//lock vars
		//loop through all philo
			//check each if they are done or dead
		//unlock
		i = 0;
		counter = 0;
		pthread_mutex_lock(&data->death_lock);
		if (data->flag == 1)
		{
			pthread_mutex_lock(&data->print_lock);
			printf("Philo died\n");
			pthread_mutex_unlock(&data->print_lock);
			pthread_mutex_unlock(&data->death_lock);
			exit(1); //wrong way to handle it ->still it never exits
		}
		pthread_mutex_unlock(&data->death_lock);
		while (i < data->philo_count)
		{
			pthread_mutex_lock(&data->meal_lock);
			if ((ft_get_time() - data->philos[i].last_meal) > data->philos[i].x_2_die)
			{
				pthread_mutex_lock(&data->death_lock);
				data->flag = 1;
				pthread_mutex_unlock(&data->death_lock);
				pthread_mutex_lock(&data->print_lock);
				printf("%d %d died\n", (ft_get_time() - *data->philos[i].start),data->philos[i].philo_id);
				pthread_mutex_unlock(&data->print_lock);
				pthread_mutex_unlock(&data->meal_lock);
				exit (1); //retun (smt)
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
					pthread_mutex_lock(&data->death_lock);
					data->flag = 1;
					pthread_mutex_unlock(&data->death_lock);
					exit (0); // return ();
				}
			}
			i++;
		}
	}
}

int	philo_creator(t_data *data)
{
	int			i;
	//pthread_t	monitor;

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
	pthread_mutex_unlock(&data->death_lock);
	if (pthread_create(&data->monitor, NULL, monitoring, data))
		return (printf("pthread_create at monitor failed\n"), cleanup_philos(data, i), 1);
	data->start = ft_get_time();
	while (++i < data->philo_count)
	{
		data->philos[i].last_meal = ft_get_time();
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]))
			return (printf("pthread_create at philos failed\n"),cleanup_philos(data, i), 1);
	}
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			data->flag = 1;
		//clean up struct after
	}
	return (0);
}

// void init_struct(t_philo **philo, int i)
// {
// 	philo[i]->philo_id = 0;
// }

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
		return (printf("DEAD\n"), 1);
	return (0);
}
