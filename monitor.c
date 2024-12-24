/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:26:11 by binary            #+#    #+#             */
/*   Updated: 2024/12/24 18:56:54 by binary           ###   ########.fr       */
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
			// printf("Monitor: Verificando philo %d, tiempo actual: %ld, last_meal: %ld\n", i, get_time(), info->phil[i].last_meal);
			pthread_mutex_lock(&info->m_meals); // protege last_meals
			// printf("%ld el time de monitor - %ld last_meal > %d to die: PHILO %d\n", get_time(), info->phil[i].last_meal, info->to_die, info->phil[i].id);
			if ((get_time() - info->phil[i].last_meal) > info->to_die)
			{
				printf("Diferencia de tiempo MONITOR %ld\n", get_time() - info->phil[i].last_meal);
				printf("Tiempo de monitor %ld del philo %d\n", info->phil[i].last_meal, info->phil[i].id);
				pthread_mutex_lock(&info->m_dead); // protege philo_dead y alive
				// pthread_mutex_lock(&info->m_print);
				info->phil[i].alive = false;
				printf("Se ha muerto el philo %d\n", info->phil->id);
				print_action(info->phil, DEAD);
				info->philo_dead = true;
				pthread_mutex_unlock(&info->m_dead);
				// pthread_mutex_unlock(&info->m_print);
				pthread_mutex_unlock(&info->m_meals);
				return (NULL);
			}
			pthread_mutex_unlock(&info->m_meals);
			i++;
		}
		i = 0;
		usleep(10000);
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
