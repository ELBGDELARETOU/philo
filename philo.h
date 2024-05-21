/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:52:25 by anaouali          #+#    #+#             */
/*   Updated: 2024/05/21 15:49:56 by anaouali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct t_info;

typedef struct t_philo
{
	int				philo_id;
	long long		finished_eating;
	int				l_fork;
	int				r_fork;
	int				eaten_meals;
	struct t_info	*info_lst;
	pthread_t		thread_id;
}					t_philo;

typedef struct t_info
{
	int				total_p_num;
	int				philo_t_die;
	int				philo_t_eat;
	int				philo_t_sleep;
	int				must_eat;
	int				eaten_all;
	int				is_dead;
	long long		time;

	pthread_mutex_t	checker;
	pthread_mutex_t	writing;
	pthread_mutex_t	forks[250];
	t_philo			philos[250];
}					t_info;

// utils
long				ft_atoi(char *str);
int					ft_strlen(char *str);
int					ft_isdigit(char c);
long long			ft_time(void);
void				ft_sleep(long long time, t_info *rules);
void				my_printf(t_info *info, int i, char *str);

// input check
bool				check_input(int argc, char **argv);

// init
bool				init(int ac, char **av, t_info *info);

// first step
int					first_step(t_info *info);

#endif