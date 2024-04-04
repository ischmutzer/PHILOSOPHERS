/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:04:45 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/04 20:04:38 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <string.h>

void	fill_struct()
{
	
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
		fill_struct();
	}
}
