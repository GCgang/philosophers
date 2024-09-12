/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:39:11 by hyeoan            #+#    #+#             */
/*   Updated: 2023/05/02 16:26:40 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s != '\0')
		write(fd, s++, 1);
}

int	print_error(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	return (-1);
}

int	error_ctl(t_manage *manage, int free_level, char *err_msg)
{
	if (free_level == FREE_LV1)
		free_lv1_lv2_lv3(manage, FREE_LV1);
	else if (free_level == FREE_LV2)
		free_lv1_lv2_lv3(manage, FREE_LV2);
	else if (free_level == FREE_LV3)
		free_lv1_lv2_lv3(manage, FREE_LV3);
	else if (free_level == FREE_LV4)
		free_lv4_lv5_lv6(manage, FREE_LV4);
	else if (free_level == FREE_LV5)
		free_lv4_lv5_lv6(manage, FREE_LV5);
	else if (free_level == FREE_LV6)
		free_lv4_lv5_lv6(manage, FREE_LV6);
	return (print_error(err_msg));
}

unsigned long long	ft_atoll(char *str)
{
	unsigned long long	result;
	unsigned long long	before;
	int					i;

	result = 0;
	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (ft_isdigit(str[i]) == 0)
		return (ULL_MAX);
	while (ft_isdigit(str[i]))
	{
		before = result;
		result = result * 10 + (str[i] - '0');
		if (before > result)
			return (ULL_MAX);
		i++;
	}
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] != '\0')
		return (ULL_MAX);
	return (result);
}

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}
