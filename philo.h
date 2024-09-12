/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:13:52 by hyeoan            #+#    #+#             */
/*   Updated: 2023/05/10 14:54:22 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define ULL_MAX 18446744073709551615ULL
# define TRUE 1
# define FALSE 0
# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIED_MSG "died"

enum	e_PHILO_STAT
{
	TAKEN_FORK = 0,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
};

enum	e_FORK_STATUS
{
	BEING_USED = 0,
	NOT_USED
};

enum	e_FREE_LEVEL
{
	FREE_LV1 = 1,
	FREE_LV2,
	FREE_LV3,
	FREE_LV4,
	FREE_LV5,
	FREE_LV6,
};

typedef struct s_args
{
	unsigned long long	philo_num;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	must_eat;
}	t_args;

typedef struct s_share_resource
{
	unsigned long long	start_time;
	unsigned long long	full_philo;
	int					died;
	int					*fork_status;
	pthread_mutex_t		m_eat;
	pthread_mutex_t		*m_forks;
	pthread_mutex_t		m_died;
	pthread_mutex_t		m_print;
}	t_share_resource;

typedef struct s_thread
{
	t_args				*args;
	unsigned long long	id;
	unsigned long long	last_meal_time;
	unsigned long long	left_fork;
	unsigned long long	right_fork;
	unsigned long long	eat_count;
	pthread_t			thread;
	t_share_resource	*share_resource;
}	t_thread;

typedef struct s_manage
{
	t_share_resource	*share_resource;
	t_thread			*philo;
}	t_manage;

/* *******************************finalize*********************************** */
/*                                                                            */
/* ************************************************************************** */
int					finalize(t_manage *manage);
void				free_lv1_lv2_lv3(t_manage *manage, int free_level);
void				free_lv4_lv5_lv6(t_manage *manage, int free_level);
int					all_destroy(t_manage *manage);

/* ******************************initialize********************************** */
/*                                                                            */
/* ************************************************************************** */
int					init_args(t_args **args, int argc, char **argv);
int					check_valid_argument(t_args *args, int argc);
int					init_manage(t_manage **manage, t_args *args);
int					init_mutex(t_manage *manage);
int					initialize(t_manage *manage);

/* *********************************main************************************* */
/*                                                                            */
/* ************************************************************************** */
int					creat_philo(t_manage *manage);
void				*only_one_philo(void *arg);
void				*routine(void *arg);
int					join_philo(t_manage *manage);
void				print_philo_status(t_thread *philo, char *status);

/* *******************************monitoring********************************* */
/*                                                                            */
/* ************************************************************************** */
int					monitoring(t_manage *manage);
int					die_philo(t_manage *manage, unsigned long long i);
int					full_philo(t_manage *manage, unsigned long long i);
int					check_died(t_thread *philo);
void				print_philo_status(t_thread *philo, char *status);

/* *********************************utils************************************ */
/*                                                                            */
/* ************************************************************************** */
void				ft_putstr_fd(char *s, int fd);
int					print_error(char *err_msg);
int					error_ctl(t_manage *manage, int free_level, char *err_msg);
int					ft_isdigit(int c);
unsigned long long	ft_atoll(char *str);

/* ********************************routine*********************************** */
/*                                                                            */
/* ************************************************************************** */
int					pickup(t_thread *philo);
int					eating(t_thread *philo);
int					sleeping(t_thread *philo);
int					thinking(t_thread *philo);
int					putdown(t_thread *philo);

/* *********************************time************************************* */
/*                                                                            */
/* ************************************************************************** */
unsigned long long	get_current_time(void);
void				msleep(unsigned long long time);

#endif
