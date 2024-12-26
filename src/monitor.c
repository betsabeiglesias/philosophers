/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:26:11 by binary            #+#    #+#             */
/*   Updated: 2024/12/26 15:48:08 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void    *monitor(void *arg)
{
    t_data	*info;
    // int     i;
	// long int	time;

    info = (t_data *)arg;
	// i = 0;
	while (1)
	{
		if (is_hungry(info))
		{
			pthread_mutex_lock(&info->m_dead);
			info->philo_dead = true;
			// printf("ESTA MUERTO EL PHILO %d\n", info->phil->id);
			pthread_mutex_unlock(&info->m_dead);
			break ;
		}
		if (check_allfull(info))
			break;
		usleep(100);
	}
	return (NULL);
}

int	is_hungry(t_data *info)
{
	int	i;
	long int	time;

	i = 0;
	// while (i < info->nb_philo && info->phigitlo_dead == false)
	while (i < info->nb_philo)
	{
		pthread_mutex_lock(&info->m_meals); // protege last_meals
		time = get_time() - info->phil[i].last_meal;
		pthread_mutex_unlock(&info->m_meals);
		if (time > info->to_die && info->phil->state != EAT)
		{
			// printf("MUERTE TIME %ld, LASTMEAL %ld\n", time, info->phil[i].last_meal);
			print_action(info->phil, DEAD);
			return (EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	return (EXIT_SUCCESS);
}


int	join_threads(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_join(info->phil[i].philo, NULL))
		{
			handle_error(ERR_THR);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	destroy_mutex(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if(pthread_mutex_destroy(&info->forks[i]))
		{
			handle_error(ERR_MUT);
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_mutex_destroy(&info->m_dead))
	{
		handle_error(ERR_MUT);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_destroy(&info->m_meals))
	{
		handle_error(ERR_MUT);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_destroy(&info->m_print))
	{
		handle_error(ERR_MUT);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}