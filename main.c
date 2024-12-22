/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:21:07 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/22 23:25:16 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	t_data	info;
	// t_philo	phil;
	pthread_t	death;
	
	printf("empezamos\n");
	if (get_args(argc, argv, &info))
		return (EXIT_FAILURE);
	if (init_mutex(&info))
		return (EXIT_FAILURE);
	init_philo(&info);
	if (init_threads (&info))
		return (EXIT_FAILURE);
	if(pthread_create(&death, NULL, monitor, &info))
	{
		handle_error(ERR_THR);
		return (EXIT_FAILURE);
	}
	finish_threads(&info);
	pthread_join(death, NULL);
	return(EXIT_SUCCESS);
}

int get_args(int argc, char **argv, t_data *info)
{
	if(check_arguments(argc, argv))
		return(EXIT_FAILURE);
	info->nb_philo = ft_atoi_philo(argv[1]);
	info->to_die = ft_atoi_philo(argv[2]);
	info->to_eat = ft_atoi_philo(argv[3]);
	info->to_sleep = ft_atoi_philo(argv[4]);
	if (argv[5])
		info->must_meals = ft_atoi_philo(argv[5]);
	else
		info->must_meals = 0;
	info->time_start = get_time();
	printf("TIME START %ld\n", info->time_start);
	info->philo_dead = false;
	printf("nb_philos: %d\n to_die: %d\n to_eat: %d\n to_sleep: %d\n must meals: %d\n", info->nb_philo, info->to_die, info->to_eat, info->to_sleep, info->must_meals);
	info->phil = malloc(sizeof(t_philo) * info->nb_philo);
	if (!info->phil)
		return(handle_error(ERR_MALL), EXIT_FAILURE);
	//printf("%p direccion de los philos\n", info->phil);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nb_philo);
	if(!info->forks)
		return(handle_error(ERR_MALL), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	init_philo(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		info->phil[i].id = i + 1;
		printf("los id de los philos: %d\n", info->phil->id);
		info->phil[i].meals_toeat = info->must_meals;
		info->phil[i].alive = true;
		info->phil[i].last_meal = 0;
		// info->phil[i].state = BIRTH;
		info->phil[i].info = info;
		info->phil[i].r_fork = &info->forks[i];
		if (info->nb_philo > 1)
			info->phil[i].l_fork = &info->forks[(i + 1) % info->nb_philo]; 
		i++;
	}
	//printf("Se han iniciado los philos\n");

}

int	init_threads(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_create(&info->phil[i].philo, NULL, &routine, &info->phil[i]))
			{
				handle_error(ERR_THR);
				return (EXIT_FAILURE);
			}
		i++;
	}	
	return (EXIT_SUCCESS);
}

int	init_mutex(t_data *info)
{
	int	i;

	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nb_philo);
	if (!info->forks)
		return (handle_error(ERR_MALL), EXIT_FAILURE);
	while (i < info->nb_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (handle_error(ERR_MUT), EXIT_FAILURE);
		i++;
	}
	if (pthread_mutex_init(&info->m_dead, NULL))
		return (handle_error(ERR_MUT), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


