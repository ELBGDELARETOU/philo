/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademnaouali <ademnaouali@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:50:58 by anaouali          #+#    #+#             */
/*   Updated: 2024/05/21 12:18:04 by ademnaouali      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

long	ft_atoi(char *str)
{
	long	atoi;
	long	signe;

	signe = 1;
	atoi = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = signe * -1;
		str++;
		if (*str == '-' || *str == '+')
			return (0);
	}
	while (*str >= '0' && *str <= '9')
	{
		atoi = (atoi * 10 + (*str - '0'));
		str++;
	}
	return (atoi * signe);
}

long long ft_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return  ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	my_printf(t_info *info, int i, char *str)
{
	pthread_mutex_lock(&(info->writing));
	printf("Time : %lld philo : %i is %s\n", (ft_time() - info->time), (i + 1), str);
	pthread_mutex_unlock(&(info->writing));
}