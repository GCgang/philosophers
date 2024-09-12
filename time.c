/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:05:31 by hyeoan            #+#    #+#             */
/*   Updated: 2023/05/02 13:13:54 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_current_time(void)
{
	struct timeval		time;
	unsigned long long	current_time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("gettimeofday error(get_current_time)\n");
	}
	current_time = time.tv_sec * 1000;
	current_time += time.tv_usec / 1000;
	return (current_time);
}

void	msleep(unsigned long long time)
{
	unsigned long long	tmp;

	tmp = get_current_time();
	while (get_current_time() - tmp < time)
		usleep(100);
}
