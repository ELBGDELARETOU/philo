/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:50:58 by anaouali          #+#    #+#             */
/*   Updated: 2024/03/11 11:50:02 by anaouali         ###   ########.fr       */
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
void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*str1;

	str1 = str;
	while (n > 0)
	{
		*str1 = c;
		n--;
		str1++;
	}
	return (str);
}
