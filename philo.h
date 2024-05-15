/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademnaouali <ademnaouali@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:52:25 by anaouali          #+#    #+#             */
/*   Updated: 2024/05/15 15:06:01 by ademnaouali      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/time.h>

struct t_info;

typedef struct t_philo
{
	int				philo_id;
	long long		finished_eating;
	int				l_fork;
	int				r_fork;
	int				eaten_meals;
	struct t_info			*info_lst;
	pthread_t		thread_id;
}					t_philo;

typedef struct t_info
{
	int				finsished;
	int				is_dead;
	int				total_p_num;
	int				philo_t_die;
	int				philo_t_eat;
	int				philo_t_sleep;
	int				philo_must_eat;
	long long		time;

	pthread_mutex_t	forks[200];
	t_philo			philos[200];
}					t_info;


// utils
long				ft_atoi(char *str);
int					ft_strlen(char *str);
int					ft_isdigit(char c);
void				*ft_memset(void *str, size_t n);
long long 			ft_time(void);

// input check
int					check_input(int argc, char **argv);

// init
bool init(int ac, char **av, t_info *info);

#endif