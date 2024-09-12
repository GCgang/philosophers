/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:19:00 by hyeoan            #+#    #+#             */
/*   Updated: 2023/05/14 13:43:26 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finalize(t_manage *manage)
{
	if (all_destroy(manage) == -1)
	{
		return (error_ctl(manage, FREE_LV6, \
								"pthread mutex destroy error(finalize)\n"));
	}
	free_lv4_lv5_lv6(manage, FREE_LV6);
	return (1);
}

int	all_destroy(t_manage *manage)
{
	unsigned long long	i;

	i = -1;
	if (pthread_mutex_destroy(&manage->share_resource->m_died) != 0 || \
		pthread_mutex_destroy(&manage->share_resource->m_eat) != 0 || \
		pthread_mutex_destroy(&manage->share_resource->m_print) != 0)
	{
		return (print_error("pthread mutex destroy error(all_destroy)\n"));
	}
	while (++i < manage->philo->args->philo_num)
	{
		if (pthread_mutex_destroy(&manage->share_resource->m_forks[i]) != 0)
		{
			return (print_error("pthread mutex destroy error(all_destroy)\n"));
		}
	}
	return (1);
}

void	free_lv1_lv2_lv3(t_manage *manage, int free_level)
{
	if (free_level == FREE_LV1)
		free(manage);
	else if (free_level == FREE_LV2)
	{
		free(manage->share_resource);
		free(manage);
	}
	else if (free_level == FREE_LV3)
	{
		free(manage->philo);
		free(manage->share_resource);
		free(manage);
	}
}

void	free_lv4_lv5_lv6(t_manage *manage, int free_level)
{
	if (free_level == FREE_LV4)
	{
		free(manage->philo->args);
		free(manage->philo);
		free(manage->share_resource);
		free(manage);
	}
	else if (free_level == FREE_LV5)
	{
		free(manage->philo->args);
		free(manage->philo);
		free(manage->share_resource->fork_status);
		free(manage->share_resource);
		free(manage);
	}
	else if (free_level == FREE_LV6)
	{
		free(manage->philo->args);
		free(manage->philo);
		free(manage->share_resource->fork_status);
		free(manage->share_resource->m_forks);
		free(manage->share_resource);
		free(manage);
	}
}
