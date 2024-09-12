/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:20:02 by hyeoan            #+#    #+#             */
/*   Updated: 2023/05/02 16:05:43 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_args **args, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (print_error("argument error (init_args)\n"));
	(*args) = (t_args *)malloc(sizeof(t_args));
	if (args == NULL)
		return (print_error("Malloc error (init_args : args)\n"));
	(*args)->philo_num = ft_atoll(argv[1]);
	(*args)->time_to_die = ft_atoll(argv[2]);
	(*args)->time_to_eat = ft_atoll(argv[3]);
	(*args)->time_to_sleep = ft_atoll(argv[4]);
	if (argc == 6)
		(*args)->must_eat = ft_atoll(argv[5]);
	return (1);
}

int	check_valid_argument(t_args *args, int argc)
{
	if ((args->philo_num == 0 || args->philo_num == ULL_MAX) \
		|| (args->time_to_die == 0 || args->time_to_die == ULL_MAX) \
		|| (args->time_to_eat == 0 || args->time_to_eat == ULL_MAX) \
		|| (args->time_to_sleep == 0 || args->time_to_sleep == ULL_MAX))
	{
		free(args);
		return (print_error("argument error (check_valid_argument)\n"));
	}
	if (argc == 6)
	{
		if (args->must_eat == 0 || args->must_eat == ULL_MAX)
		{
			free (args);
			return (print_error("argument error (check_valid_argument)\n"));
		}
	}
	return (1);
}

int	init_manage(t_manage **manage, t_args *args)
{
	*manage = (t_manage *)malloc(sizeof(t_manage));
	if (*manage == NULL)
		return (free(args), \
					print_error("Malloc error(init_manage : manage)\n"));
	(*manage)->share_resource = \
						(t_share_resource *)malloc(sizeof(t_share_resource));
	if ((*manage)->share_resource == NULL)
		return (free(args), error_ctl(*manage, FREE_LV1, \
					"Malloc error (init_manage : share_resource)\n"));
	(*manage)->philo = (t_thread *)malloc(sizeof(t_thread) * args->philo_num);
	if ((*manage)->philo == NULL)
		return (free(args), error_ctl(*manage, FREE_LV2, \
								"Malloc error (init_manage : philo)\n"));
	(*manage)->philo->args = args;
	(*manage)->share_resource->fork_status = (int *)malloc(sizeof(int) * \
							(*manage)->philo->args->philo_num);
	if ((*manage)->share_resource->fork_status == NULL)
		return (error_ctl(*manage, FREE_LV4, \
						"Malloc error (init_manage : fork_status)\n"));
	(*manage)->share_resource->m_forks = (pthread_mutex_t *)malloc \
		(sizeof(pthread_mutex_t) * (*manage)->philo->args->philo_num);
	if ((*manage)->share_resource->m_forks == NULL)
		return (error_ctl(*manage, FREE_LV5, \
							"Malloc error (init_manage : m_forks)\n"));
	return (1);
}

int	init_mutex(t_manage *manage)
{
	unsigned long long	i;

	i = -1;
	if (pthread_mutex_init(&manage->share_resource->m_eat, NULL) != 0 || \
		pthread_mutex_init(&manage->share_resource->m_print, NULL) != 0 || \
		pthread_mutex_init(&manage->share_resource->m_died, NULL) != 0)
	{
		return (error_ctl(manage, FREE_LV6, "mutex init error(init_mutex)\n"));
	}
	while (++i < manage->philo->args->philo_num)
	{
		if (pthread_mutex_init(&manage->share_resource->m_forks[i], NULL) != 0)
			return (error_ctl(manage, FREE_LV6, \
											"mutex init error(init_mutex)\n"));
	}
	return (1);
}

int	initialize(t_manage *manage)
{
	unsigned long long	i;

	i = -1;
	manage->share_resource->full_philo = 0;
	manage->share_resource->died = FALSE;
	manage->share_resource->start_time = get_current_time();
	while (++i < manage->philo->args->philo_num)
	{
		manage->share_resource->fork_status[i] = NOT_USED;
		manage->philo[i].args = manage->philo->args;
		manage->philo[i].id = i;
		manage->philo[i].last_meal_time = manage->share_resource->start_time;
		manage->philo[i].eat_count = 0;
		manage->philo[i].left_fork = i;
		manage->philo[i].right_fork = (i + 1) % \
							manage->philo->args->philo_num;
		manage->philo[i].share_resource = manage->share_resource;
	}
	return (1);
}
