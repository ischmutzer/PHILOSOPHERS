/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:44:06 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/29 19:35:44 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->meal_lock);
	while (++i < data->philo_count)
		pthread_mutex_destroy(&data->forks[i]);
}

void	cleanup_philos(t_data *data, int index)
{
	int	i;

	i = 0;
	if (index == -1)
	{
		if (pthread_join(data->monitor, NULL) != 0)
			change_flag(data);
		return ;
	}
	else
	{
		while (i < index)
		{
			if (pthread_join(data->philos[i].thread, NULL) != 0)
				change_flag(data);
			i++;
		}
	}
	destroy_mutexes(data);
	free(data->philos);
}
