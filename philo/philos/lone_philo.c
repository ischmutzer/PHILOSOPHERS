/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lone_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:25:39 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/31 13:26:34 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	ft_usleep(philo, philo->x_2_die);
	pthread_mutex_unlock(philo->left_fork);
	print_philos(philo, philo->philo_id, "died");
	return (NULL);
}

void	handle_one_philo(t_data *data)
{
	data->start = ft_get_time();
	if (pthread_create(&data->philos[0].thread, NULL,
			lone_philo, &data->philos[0]))
		return (change_flag(data), cleanup_philos(data, data->philo_count));
	cleanup_philos(data, data->philo_count);
}
