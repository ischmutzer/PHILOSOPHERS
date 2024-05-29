/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:30:52 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/29 20:06:46 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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
				print_monitor(data, data->philos[i].philo_id, "died");
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

// void	*monitoring(void *arg)
// {
// 	t_data	*data = (t_data*)arg;
// 	int		i;
// 	int		counter;

// 	while (1)
// 	{
// 		i = 0;
// 		counter = 0;
// 		while (i < data->philo_count)
// 		{
// 			pthread_mutex_lock(&data->meal_lock);
// 			if ((ft_get_time() - data->philos[i].last_meal) > (size_t)data->philos[i].x_2_die)
// 			{
// 				change_flag(data);
// 				print_monitor(data, data->philos[i].philo_id, "died");
// 				pthread_mutex_unlock(&data->meal_lock);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&data->meal_lock);
// 			if (data->num_meals != -1)
// 			{
// 				pthread_mutex_lock(&data->meal_lock);
// 				if (data->philos[i].meals_eaten >= data->num_meals)
// 					counter++;
// 				pthread_mutex_unlock(&data->meal_lock);
// 				if (counter == data->philo_count)
// 				{
// 					change_flag(data);
// 					return (NULL);
// 				}
// 			}
// 			i++;
// 		}
// 		// REMOVE ITS ONLY FOR VALGRIND
// 		usleep(200);
// 	}
// }
