/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:04:45 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/15 19:41:36 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/pthreadtypes.h>
//#include <cstdlib>
#include <pthread.h>
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

void	*philo_routine(void *arg)
{
	t_data	*data;
	t_args	*args;

	data = (t_data *)arg;
	args = &data->args;
	while (1)
	{
		//eat
		//sleep
		//think
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
