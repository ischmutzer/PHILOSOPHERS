/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:35:35 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/29 19:40:07 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print_philos(t_philo *philo, int id, char *msg)
{
	if (lock_death(philo) == 1)
		return ;
	pthread_mutex_lock(philo->print_lock);
	printf("%lu %d %s\n", (ft_get_time() - *(philo->start)), id, msg);
	pthread_mutex_unlock(philo->print_lock);
}

int	lock_death(t_philo *philo)
{
	pthread_mutex_lock(philo->death_lock);
	if (*(philo->dead_philo) == 1)
	{
		pthread_mutex_unlock(philo->death_lock);
		return (1);
	}
	else
		pthread_mutex_unlock(philo->death_lock);
	return (0);
}

void	philo_is_eating(t_philo *philo)
{
	if (lock_death(philo) == 1)
		return ;
	pthread_mutex_lock(philo->meal_lock);
	++philo->meals_eaten;
	pthread_mutex_unlock(philo->meal_lock);
}

void	philo_finished_eating(t_philo *philo)
{
	if (lock_death(philo) == 1)
		return ;
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(philo->meal_lock);
}
