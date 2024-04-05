/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:04:45 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/05 17:28:28 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/pthreadtypes.h>
#include <cstdlib>
#include <pthread.h>
#include <string.h>

void	fill_data_struct(t_data *data, char **philo_info)
{
	data->num_philo = atoi(philo_info[0]); //change to my own atoi
	data->x_to_die = atoi(philo_info[1]); //change to my own atoi
	data->x_to_eat = atoi(philo_info[2]); //change to my own atoi
	data->x_to_sleep = atoi(philo_info[3]); //change to my own atoi
	if (philo_info[4])
		data->num_x_philo_eat = atoi(philo_info[4]); //change to my own atoi
	else
	 	data->num_x_philo_eat = -1;
}

void	philo_creator(t_data *data)
{
	int			i;
	pthread_t	philo[data->num_philo];

	i = -1;
	while (++i <= data->num_philo)
	{
		if (pthread_create(&philo[i], NULL, void *(*start_routine)(void *), void *restrict arg) != 0)
			return ; //thread was not created, handle it
	}
}

//argv[0] = philo_count (n° of forks)
//argv[1] = time to die
//argv[2] = time to eat
//argv[3] = time to sleep
//argv[4] = number of times each philo must eat (optional arg)
int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = -1;
	memset(&data, '0', sizeof(data)); //are t_args getting initialized?
	/* printf("hej filip\n");
	usleep(500000);
	printf("hej ildiko\n");*/
	if (argc == 4 || argc == 5)
	{
		fill_data_struct(&data, argv);
	}
}
