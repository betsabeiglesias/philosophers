/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:21:07 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/25 20:34:18 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int main(int argc, char **argv)
{
	t_data		info;
	pthread_t	death;
	
	if (get_args(argc, argv, &info))
		return (EXIT_FAILURE);
	init_philo(&info);
	if (init_threads (&info))
		return (EXIT_FAILURE);
	usleep(100);
	if (pthread_create(&death, NULL, monitor, &info))
	{
		handle_error(ERR_THR);
		return (EXIT_FAILURE);
	}
	join_threads(&info);
	pthread_join(death, NULL);
	destroy_mutex(&info);
	frees(&info);
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
		info->must_meals = -1;
	info->time_start = get_time();
	info->philo_dead = false;
	info->phil = malloc(sizeof(t_philo) * info->nb_philo);
	if (!info->phil)
		return(handle_error(ERR_MALL), EXIT_FAILURE);
	if (init_mutex(info))
		return(handle_error(ERR_THR), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	init_philo(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		info->phil[i].id = i + 1;
		info->phil[i].meals_eaten = 0;
		info->phil[i].last_meal = get_time();
		// printf("%ld last meal del philo %d\n", info->phil[i].last_meal, info->phil[i].id);
		info->phil[i].state = BIRTH;
		info->phil[i].info = info;
		info->phil[i].r_fork = &info->forks[i];
		if (info->nb_philo > 1)
		{
			info->phil[i].l_fork = &info->forks[(i + 1) % info->nb_philo];
		}
		i++;
	}
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
		// printf("Se crea el hilo philo %d\n", info->phil[i].id);
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
	if (pthread_mutex_init(&info->m_meals, NULL))
		return (handle_error(ERR_MUT), EXIT_FAILURE);
	if (pthread_mutex_init(&info->m_print, NULL))
		return (handle_error(ERR_MUT), EXIT_FAILURE);
	// if (pthread_mutex_init(&info->m_state, NULL))
	// 	return (handle_error(ERR_MUT), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

