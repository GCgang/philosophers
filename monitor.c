/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:57:16 by hyeoan            #+#    #+#             */
/*   Updated: 2023/05/11 14:57:54 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring(t_manage *manage)
{
	unsigned long long	i;

	while (1)
	{
		i = -1;
		while (++i < manage->philo->args->philo_num)
		{
			pthread_mutex_lock(&manage->philo[i].share_resource->m_eat);
			if (get_current_time() - manage->philo[i].last_meal_time >= \
				manage->philo->args->time_to_die)
			{
				pthread_mutex_unlock(&manage->philo[i].share_resource->m_eat);
				return (die_philo(manage, i));
			}
			if (manage->philo->args->must_eat != 0 && \
		(manage->share_resource->full_philo == manage->philo->args->philo_num))
			{
				pthread_mutex_unlock(&manage->philo[i].share_resource->m_eat);
				return (full_philo(manage, i));
			}
			pthread_mutex_unlock(&manage->philo[i].share_resource->m_eat);
		}
	}
	return (1);
}

int	die_philo(t_manage *manage, unsigned long long i)
{
	print_philo_status(&manage->philo[i], DIED_MSG);
	pthread_mutex_lock(&manage->share_resource->m_died);
	manage->share_resource->died = TRUE;
	pthread_mutex_unlock(&manage->philo[i].share_resource->m_died);
	return (1);
}

int	full_philo(t_manage *manage, unsigned long long i)
{
	pthread_mutex_lock(&manage->share_resource->m_died);
	manage->share_resource->died = TRUE;
	pthread_mutex_unlock(&manage->philo[i].share_resource->m_died);
	return (1);
}

int	check_died(t_thread *philo)
{
	pthread_mutex_lock(&philo->share_resource->m_died);
	if (philo->share_resource->died == TRUE)
	{
		pthread_mutex_unlock(&philo->share_resource->m_died);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->share_resource->m_died);
	return (FALSE);
}

void	print_philo_status(t_thread *philo, char *status)
{
	unsigned long long	current_time;

	pthread_mutex_lock(&philo->share_resource->m_print);
	pthread_mutex_lock(&philo->share_resource->m_died);
	current_time = get_current_time();
	if (philo->share_resource->died == FALSE)
	{
		printf("%llu %llu %s\n", \
			current_time - philo->share_resource->start_time, philo->id + 1, \
			status);
	}
	pthread_mutex_unlock(&philo->share_resource->m_died);
	pthread_mutex_unlock(&philo->share_resource->m_print);
}
