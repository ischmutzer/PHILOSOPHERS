/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:04:45 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/16 15:26:38 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/pthreadtypes.h>
//#include <cstdlib>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

// void	*monitor(void *data)
// {
// 	while (1)
// 	{
// 		if (data->meals_eaten == data->num_meals)
// 		{
// 			data->dead_philo = 1;
// 			break;
// 		}
// 		//else if (data->dead_philo) -> if philo died -> break
// 		//	break;
// 	}
// }

//is it correct to use data and not philos? shouldnt it be
//accesing the philos struct at [i]?
void	*philo_routine(void *arg)
{
	t_data *data = (t_data*) arg;
	while (1)
	{
		if (data->philos->philo_id % 2 == 0)
			pthread_mutex_lock(data->philos->left_fork);
		else
			pthread_mutex_lock(data->philos->right_fork);
		printf("%d %d has taken a fork\n", (ft_get_time() - data->philos->start), data->philos->philo_id);
		if (data->philos->philo_id % 2 == 0)
			pthread_mutex_lock(data->philos->right_fork);
		else
			pthread_mutex_lock(data->philos->left_fork);
		printf("%d %d has taken a fork\n", (ft_get_time() - data->philos->start), data->philos->philo_id);
		data->philos->is_eating = 1;
		printf("%d %d is eating\n", (ft_get_time() - data->philos->start), data->philos->philo_id);
		ft_usleep(data, data->philos->x_2_eat);
		++data->philos->meals_eaten;
		data->philos->last_meal = ft_get_time();
		data->philos->is_eating = 0;
		pthread_mutex_unlock(data->philos->left_fork);
		pthread_mutex_unlock(data->philos->right_fork);
		pthread_mutex_lock(data->philos->print_lock);
		printf("%d %d is sleeping\n", (ft_get_time() - data->philos->start), data->philos->philo_id);
		pthread_mutex_unlock(data->philos->print_lock);
		ft_usleep(data, data->philos->x_2_sleep);
		pthread_mutex_lock(data->philos->print_lock);
		printf("%d %d is thinking\n", (ft_get_time() - data->philos->start), data->philos->philo_id);
		pthread_mutex_unlock(data->philos->print_lock);
	}
}

void	philo_creator(t_data *data)
{
	int			i;

	i = -1;
	if (data->flag == 1)
	{
		printf("Philo is dead\n");
		return ;
	}
	while (++i < data->philos[0].num_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]))
			printf("Error: pthread_create failed\n");
	}
	pthread_join(data->philos[0].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			philos[MAX_COUNT];
	pthread_mutex_t	forks[MAX_COUNT];
	int				philo_count;
	int				i;

	i = -1;
	if (check_whether_valid_input(argc, argv))
		return (1);
	philo_count = philo_atoi(argv[1]);
	data_init(&data, philo_count);
	forks_init(forks, philo_count);
	philos_init(&data, forks, philos, argv);
	return (0);
}
