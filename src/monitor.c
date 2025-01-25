/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:26:11 by binary            #+#    #+#             */
/*   Updated: 2025/01/25 13:18:09 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*monitor(void *arg)
{
	t_data	*info;

	info = (t_data *)arg;
	while (1)
	{
		if (is_hungry(info))
		{
			pthread_mutex_lock(&info->m_dead);
			info->philo_dead = true;
			pthread_mutex_unlock(&info->m_dead);
			break ;
		}
		if (check_allfull(info))
			break ;
		usleep(100);
	}
	return (NULL);
}

int	is_hungry(t_data *info)
{
	int			i;
	long int	time;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_lock(&info->m_meals);
		time = get_time() - info->phil[i].last_meal;
		pthread_mutex_unlock(&info->m_meals);
		if (time > info->to_die)
		{
			print_action(info->phil, DEAD);
			return (EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	return (EXIT_SUCCESS);
}

int	check_someonedead(t_data *info)
{
	pthread_mutex_lock(&info->m_dead);
	if (info->philo_dead == true)
	{
		pthread_mutex_unlock(&info->m_dead);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&info->m_dead);
	return (EXIT_SUCCESS);
}

bool	check_allfull(t_data *info)
{
	bool	all_full;

	pthread_mutex_lock(&info->m_meals);
	all_full = info->full;
	pthread_mutex_unlock(&info->m_meals);
	return (all_full);
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
