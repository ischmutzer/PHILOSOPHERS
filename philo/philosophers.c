/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:04:45 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/15 17:01:29 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/pthreadtypes.h>
//#include <cstdlib>
#include <pthread.h>
#include <string.h>

void	fill_data_struct(t_data *data, char **philo_info)
{
	data->num_philo = philo_atoi(philo_info[0]);
	data->death_time = philo_atoi(philo_info[1]);
	data->meal_time = philo_atoi(philo_info[2]);
	data->sleepy_time = philo_atoi(philo_info[3]);
	if (philo_info[4])
		data->num_meals = philo_atoi(philo_info[4]);
	else
	 	data->num_meals = -1;
}

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

void	philo_creator(t_data *data)
{
	int			i;
	pthread_t	philo[data->num_philo];

	i = -1;
	while (++i < data->num_philo)
	{
		//fill 
		// if (i == data->num_philo)
		// 	pthread_create(&philo[i], NULL, monitor, data);
		if (pthread_create(&philo[i], NULL, philo_routine, data))
			printf("Error: pthread_create failed\n");
	}
}

int	check_whether_valid_input(int argc, char **args)
{
	int	num;
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (argc == 5 || argc == 6)
	{
		while (args[++i])
		{
			num = philo_atoi(args[i]);
			if (num)
			{
				if (num < 0)
					return (printf("Error: wrong argument\n"), 1);
				if (args[2] && num == 0)
					return (printf("Error: meals to be eaten is invalid\n"), 1);
			}
		}
		return (0);
	}
	else
		return (printf("Error: wrong number of arguments\n"), 1);
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
	 if (!check_whether_valid_input(argc, argv))
	 	return (1);
	memset(&data, '0', sizeof(data)); //are t_args getting initialized?
	/* printf("hej filip\n");
	usleep(500000);
	printf("hej ildiko\n");*/
	if (argc == 4 || argc == 5)
	{
		//fill_data_struct(&data, argv);
	}
	return (0);
}
