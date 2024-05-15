/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:56:58 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/15 17:01:58 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

//x = time in ms
typedef struct s_philo
{
	int	philo_id; //current philo
	int	x_2_die;
	int	x_2_eat;
	int	x_2_sleep;
	int	num_x_philo_eat;
}	t_philo;

typedef struct s_data
{
	t_philo	*philos;
	int		num_philo;
	int		death_time;
	int		meal_time;
	int		sleepy_time;
	int		num_meals;

	int		meals_eaten;
	int		dead_philo;
	
}	t_data;

int	philo_atoi(const char *str);

#endif