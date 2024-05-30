/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:30:52 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/30 15:28:16 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <pthread.h>

// int	check_meals_eaten(t_data *data, int index, int *counter)
// {
// 	pthread_mutex_lock(&data->meal_lock);
// 	if (data->philos[index].meals_eaten >= data->num_meals)
// 		(*counter++);
// 	pthread_mutex_unlock(&data->meal_lock);
// 	if (*counter == data->philo_count)
// 	{
// 		change_flag(data);
// 		return (1);
// 	}
// 	return (0);
// }

int	monitoring_checking_segment(t_data *data, int i, int counter)
{
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_lock);
		if ((ft_get_time() - data->philos[i].last_meal)
			> (size_t)data->philos[i].x_2_die)
		{
			change_flag(data);
			print_monitor(data, data->philos[i].philo_id, "died");
			pthread_mutex_unlock(&data->meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->meal_lock);
		if (data->num_meals != -1)
		{
			pthread_mutex_lock(&data->meal_lock);
			if (data->philos[i].meals_eaten >= data->num_meals)
				counter++;
			pthread_mutex_unlock(&data->meal_lock);
			if (counter == data->philo_count)
				return (change_flag(data), 1);
		}
		i++;
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_data	*data;
	int		i;
	int		counter;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		counter = 0;
		if (monitoring_checking_segment(data, i, counter))
			return (NULL);
		// REMOVE ITS ONLY FOR VALGRIND
		usleep(200);
	}
}
