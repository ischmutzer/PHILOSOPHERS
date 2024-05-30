/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:02:26 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/30 19:41:27 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <pthread.h>

size_t	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("Error: gettimeofday failed\n"), 1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static void	simulation_fail(t_philo *philo)
{
	pthread_mutex_lock(philo->death_lock);
	*(philo->dead_philo) = 1;
	pthread_mutex_unlock(philo->death_lock);
}

int	ft_usleep(t_philo *philo, int time)
{
	size_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < (size_t)time)
	{
		pthread_mutex_lock(philo->death_lock);
		if (*(philo->dead_philo) == 1)
		{
			pthread_mutex_unlock(philo->death_lock);
			return (1);
		}
		pthread_mutex_unlock(philo->death_lock);
		if (usleep(50) == -1)
			return (printf("usleep failed\n"), simulation_fail(philo), 1);
	}
	return (0);
}
