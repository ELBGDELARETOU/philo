
#include "philo.h"

bool	init_mutex(t_info *info)
{
	int i;

	i = info->total_p_num;
	while (i-- > 0)
	{
		if(pthread_mutex_init(&(info->forks[i]), NULL))
			return(false);
	}
	return(true);
}
void	init_my_philos(t_info *info)
{
	int	i;

	i = info->total_p_num;
	while(i-- >= 0)
	{
		info->philos[i].philo_id = i;
		info->philos[i].l_fork = i;
		info->philos[i].r_fork = (i + 1) % info->total_p_num;
		info->philos[i].eaten_meals = 0; 
		info->philos[i].info_lst = info;
	}
}

void	get_my_infos(int ac, char **av, t_info *info)
{
	info->total_p_num = ft_atoi(av[1]);
	info->philo_t_die = ft_atoi(av[2]);
	info->philo_t_eat = ft_atoi(av[3]);
	info->philo_t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->philo_must_eat = ft_atoi(av[5]);
    else 
        info->philo_must_eat = -1;
}

bool init(int ac, char **av, t_info *info)
{
	get_my_infos(ac, av, info);
	if (init_mutex(info) == false)
		return(printf("Mutex probleme\n"),false);
	init_my_philos(info);
	return (true);
}