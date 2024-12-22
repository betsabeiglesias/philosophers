/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:26:11 by binary            #+#    #+#             */
/*   Updated: 2024/12/22 23:08:51 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void    *monitor(void *arg)
{
    t_data	*info;
    int     i;

    info = (t_data *)arg;
	i = 0;
	while (1)
	{
    	while (i < info->nb_philo)
		{
			pthread_mutex_lock(&info->m_meals); // protege last_meals
			if (get_time() - info->phil[i].last_meal > info->to_die)
			{
				pthread_mutex_lock(&info->m_dead); // protege philo_dead y alive
				pthread_mutex_lock(&info->m_print);
				info->phil[i].alive = false;
				print_action(info->phil, DEAD);
				info->philo_dead = true;
				pthread_mutex_unlock(&info->m_dead);
				pthread_mutex_unlock(&info->m_print);
				pthread_mutex_unlock(&info->m_meals);
				return (NULL);
			}
			pthread_mutex_unlock(&info->m_meals);
			i++;
		}
		i = 0;
		usleep(1000);
	}
	return (NULL);
}

int	finish_threads(t_data *info)
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
