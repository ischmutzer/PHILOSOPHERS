/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:04:45 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/02 17:00:47 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <string.h>

void	fill_struct()
{
	
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = -1;
	memset(&data, '0', sizeof(data)); //are t_args getting initialized?
	/* printf("hej filip\n");
	usleep(500000);
	printf("hej ildiko\n"); */
	if (argc == 5 || argc == 6)
	{
		fill_struct();
	}
}
