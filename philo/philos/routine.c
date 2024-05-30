/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:10:25 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/30 15:32:50 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	pickup_forks(int counter, t_philo *philo)
{
	if (counter == 0)
	{
		if (philo->philo_id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
			return (0);
		}
		else
			if (ft_usleep(philo, (philo->x_2_eat - 0.05)) == 1)
				return (1);
	}
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		usleep(50);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	return (0);
}

void	drop_forks(t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	routine_segment(t_philo *philo)
{
	print_philos(philo, philo->philo_id, "has taken a fork");
	print_philos(philo, philo->philo_id, "has taken a fork");
	philo_is_eating(philo);
	print_philos(philo, philo->philo_id, "is eating");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		count;

	philo = (t_philo *)arg;
	count = 0;
	while (1)
	{
		if (lock_death(philo) == 1)
			return (NULL);
		if (pickup_forks(count, philo) == 1)
			return (NULL);
		routine_segment(philo);
		if (ft_usleep(philo, philo->x_2_eat) == 1)
			return (drop_forks(philo), NULL);
		philo_finished_eating(philo);
		drop_forks(philo);
		print_philos(philo, philo->philo_id, "is sleeping");
		if (ft_usleep(philo, philo->x_2_sleep) == 1)
			return (NULL);
		print_philos(philo, philo->philo_id, "is thinking");
		usleep(50);
		count++;
	}
}
