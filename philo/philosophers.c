/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:04:45 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/15 19:29:06 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/pthreadtypes.h>
//#include <cstdlib>
#include <pthread.h>
#include <string.h>

// void	fill_data_struct(t_data *data, char **philo_info)
// {
// 	data->num_philo = philo_atoi(philo_info[0]);
// 	data->death_time = philo_atoi(philo_info[1]);
// 	data->meal_time = philo_atoi(philo_info[2]);
// 	data->sleepy_time = philo_atoi(philo_info[3]);
// 	if (philo_info[4])
// 		data->num_meals = philo_atoi(philo_info[4]);
// 	else
// 	 	data->num_meals = -1;
// }

// void	*philo_routine(void *arg)
// {
// 	t_data	*data;
// 	t_args	*args;

// 	data = (t_data *)arg;
// 	args = &data->args;
// 	while (1)
// 	{
// 		//eat
// 		//sleep
// 		//think
// 	}
// }

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

// void	philo_creator(t_data *data)
// {
// 	int			i;

// 	i = -1;
// 	while (++i < data->num_philo)
// 	{
// 		//fill 
// 		// if (i == data->num_philo)
// 		// 	pthread_create(&philo[i], NULL, monitor, data);

// 		if (pthread_create(&philo[i], NULL, philo_routine, data))
// 			printf("Error: pthread_create failed\n");
// 	}
// }

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philos;
	pthread_mutex_t	*forks = NULL;
	int				philo_count;
	int				i;

	i = -1;
	if (!check_whether_valid_input(argc, argv))
		return (1);
	philo_count = philo_atoi(argv[1]);
	philos = data_init(&data, philo_count);
	forks_init(&forks[philo_count], philo_count);
	philos_init(&data, forks, philos, argv);
	return (0);
}
