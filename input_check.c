/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademnaouali <ademnaouali@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:32:06 by anaouali          #+#    #+#             */
/*   Updated: 2024/05/14 17:58:02 by ademnaouali      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	bigger_than_int(char *str)
{
	int	signe;

	signe = 1;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		signe = signe * -1;
	str++;
	if (*str == '-' || *str == '+')
		return (0);
	return (signe);
}

int	ft_is_a_valid_num(char *argv, int i)
{
	if (i == 5)
	{
		if (ft_strlen(argv) > 12 || (bigger_than_int(argv) > 0
				&& ft_atoi(argv) < 0))
			return (0);
		else
			return (1);
	}
	if (ft_strlen(argv) > 12 || (bigger_than_int(argv) > 0
			&& ft_atoi(argv) <= 0))
		return (0);
	if (ft_atoi(argv) <= 1)
		return (0);
	return (1);
}

int	ft_isalpha(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!((s[i] >= '0' && s[i] <= '9') || s[i] == '+'))
			return (0);
	return (1);
}

int	check_valid_argument(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_isalpha(argv[i]))
			return (0);
		if (!ft_is_a_valid_num(argv[i], i))
			return (0);
		i++;
	}
	return (1);
}

int	check_input(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (!(check_valid_argument(argc, argv)))
			return (printf("Check your arguments... Somthing's wrong !\n"), 0);
		return (1);
	}
	else
		return (printf("Wrong number of arguments\n"), 0);
}
