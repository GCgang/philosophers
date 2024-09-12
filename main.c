/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:09:58 by hyeoan            #+#    #+#             */
/*   Updated: 2023/05/12 20:23:13 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	creat_philo(t_manage *manage)
{
	unsigned long long	i;

	i = -1;
	while (++i < manage->philo->args->philo_num)
	{
		if (manage->philo->args->philo_num == 1)
		{
			if (pthread_create(&manage->philo[i].thread, NULL, \
				only_one_philo, (void *)&manage->philo[i]) != 0)
			{
				all_destroy(manage);
				return (error_ctl(manage, FREE_LV6, \
										"pthread create error(create_philo)\n"));
			}
			break ;
		}
		if (pthread_create(&manage->philo[i].thread, NULL, \
			routine, (void *)&manage->philo[i]) != 0)
		{
			all_destroy(manage);
			return (error_ctl(manage, FREE_LV6, \
										"pthread create error(create_philo)\n"));
		}
	}
	return (1);
}

void	*only_one_philo(void *arg)
{
	t_thread	*philo;

	philo = (t_thread *)arg;
	pthread_mutex_lock(&philo->share_resource->m_forks[philo->left_fork]);
	print_philo_status(philo, FORK_MSG);
	pthread_mutex_unlock(&philo->share_resource->m_forks[philo->left_fork]);
	return ((void *)philo);
}

void	*routine(void *arg)
{
	t_thread	*philo;

	philo = (t_thread *)arg;
	if (philo->id % 2 == 1)
		usleep(philo->args->time_to_eat * 0.8 * 1000);
	while (1)
	{
		if (pickup(philo) == 0)
			break ;
		if (eating(philo) == 0)
			break ;
		if (putdown(philo) == 0)
			break ;
		if (sleeping(philo) == 0)
			break ;
		if (thinking(philo) == 0)
			break ;
	}
	return ((void *)philo);
}

int	join_philo(t_manage *manage)
{
	unsigned long long	i;

	i = -1;
	while (++i < manage->philo->args->philo_num)
	{
		if (pthread_join(manage->philo[i].thread, NULL) != 0)
		{
			all_destroy(manage);
			return (error_ctl(manage, FREE_LV6, \
										"pthread join error(join_philo)\n"));
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_manage		*manage;
	t_args			*args;

	if (init_args(&args, argc, argv) == -1)
		return (1);
	if (check_valid_argument(args, argc) == -1)
		return (1);
	if (init_manage(&manage, args) == -1)
		return (1);
	if (initialize(manage) == -1)
		return (1);
	if (init_mutex(manage) == -1)
		return (1);
	if (creat_philo(manage) == -1)
		return (1);
	if (monitoring(manage) == -1)
		return (1);
	if (join_philo(manage) == -1)
		return (1);
	if (finalize(manage) == -1)
		return (1);
	return (0);
}
