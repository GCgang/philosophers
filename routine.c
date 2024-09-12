/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:28:40 by hyeoan            #+#    #+#             */
/*   Updated: 2023/05/14 13:23:20 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pickup(t_thread *philo)
{
	if (check_died(philo) == TRUE)
		return (0);
	pthread_mutex_lock(&philo->share_resource->m_forks[philo->left_fork]);
	philo->share_resource->fork_status[philo->left_fork] = BEING_USED;
	print_philo_status(philo, FORK_MSG);
	pthread_mutex_lock(&philo->share_resource->m_forks[philo->right_fork]);
	philo->share_resource->fork_status[philo->right_fork] = BEING_USED;
	print_philo_status(philo, FORK_MSG);
	return (1);
}

int	eating(t_thread *philo)
{
	if (check_died(philo) == TRUE) 
	{
		pthread_mutex_unlock(&philo->share_resource->m_forks[philo->left_fork]);
		pthread_mutex_unlock \
						(&philo->share_resource->m_forks[philo->right_fork]);
		return (0);
	}
	print_philo_status(philo, EAT_MSG);
	pthread_mutex_lock(&philo->share_resource->m_eat);
	philo->eat_count++;
	if (philo->eat_count == philo->args->must_eat)
		philo->share_resource->full_philo++;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->share_resource->m_eat);
	msleep(philo->args->time_to_eat);
	return (1);
}

int	sleeping(t_thread *philo)
{
	if (check_died(philo) == TRUE)
		return (0);
	print_philo_status(philo, SLEEP_MSG);
	msleep(philo->args->time_to_sleep);
	return (1);
}

int	thinking(t_thread *philo)
{
	if (check_died(philo) == TRUE)
		return (0);
	print_philo_status(philo, THINK_MSG);
	return (1);
}

int	putdown(t_thread *philo)
{
	philo->share_resource->fork_status[philo->left_fork] = NOT_USED;
	pthread_mutex_unlock(&philo->share_resource->m_forks[philo->left_fork]);
	philo->share_resource->fork_status[philo->right_fork] = NOT_USED;
	pthread_mutex_unlock(&philo->share_resource->m_forks[philo->right_fork]);
	return (1);
}
