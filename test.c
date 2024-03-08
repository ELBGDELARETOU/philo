/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:00:50 by anaouali          #+#    #+#             */
/*   Updated: 2024/03/06 11:28:31 by anaouali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t	mutex;

void	*routine_of_a_philo(void *arg)
{
	pthread_mutex_lock(&mutex);
	printf("philo is eating\n");
	// printf("philo is sleeping\n");
	// printf("philo is thinking\n");
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	t[2];
	int			i = 0;

	pthread_mutex_init(&mutex, NULL);
	while (i < 2)
	{
		// printf("philo: %d created\n", i);
		if (pthread_create(&t[i], NULL, &routine_of_a_philo, NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		// printf("philo: %d destroyed\n", i);
		if (pthread_join(t[i], NULL) != 0)
			return (1);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}

