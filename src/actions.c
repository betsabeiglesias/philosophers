/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:17:25 by binary            #+#    #+#             */
/*   Updated: 2024/12/29 19:50:13 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	eating(t_philo *phil)
{
	if (check_someonedead(phil->info) || check_allfull(phil->info))
		return (EXIT_FAILURE);
	lock_forks(phil);
	if (check_someonedead(phil->info))
	{
		unlock_forks(phil);
		return (EXIT_FAILURE);
	}
	print_action(phil, EAT);
	pthread_mutex_lock(&phil->info->m_state);
	phil->state = EATSTATE;
	pthread_mutex_unlock(&phil->info->m_state);
	usleep(phil->info->to_eat * 1000);
	pthread_mutex_lock(&phil->info->m_meals);
	phil->last_meal = get_time();
	pthread_mutex_unlock(&phil->info->m_meals);
	unlock_forks(phil);
	if (phil->info->must_meals > 0 \
		&& phil->meals_eaten < phil->info->must_meals)
		phil->meals_eaten++;
	count_meals_eaten(phil);
	return (EXIT_SUCCESS);
}

int	sleeping(t_philo *phil)
{
	if (check_someonedead(phil->info) || check_allfull(phil->info))
		return (EXIT_FAILURE);
	print_action(phil, SLEEP);
	usleep(phil->info->to_sleep * 1000);
	pthread_mutex_lock(&phil->info->m_state);
	phil->state = SLEEPSTATE;
	pthread_mutex_unlock(&phil->info->m_state);
	return (EXIT_SUCCESS);
}

int	thinking(t_philo *phil)
{
	if (check_someonedead(phil->info) || check_allfull(phil->info))
		return (EXIT_FAILURE);
	print_action(phil, THINK);
	pthread_mutex_lock(&phil->info->m_state);
	phil->state = THINKSTATE;
	pthread_mutex_unlock(&phil->info->m_state);
	return (EXIT_SUCCESS);
}

int	count_meals_eaten(t_philo *phil)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < phil->info->nb_philo)
	{
		pthread_mutex_lock(&phil->info->m_meals);
		if (phil->info->must_meals != -1 && \
			phil->info->phil[i].meals_eaten == phil->info->must_meals)
		{
			full++;
			if (full == phil->info->nb_philo)
			{
				phil->info->full = true;
				pthread_mutex_unlock(&phil->info->m_meals);
				return (EXIT_FAILURE);
			}
		}
		pthread_mutex_unlock(&phil->info->m_meals);
		i++;
	}
	return (EXIT_SUCCESS);
}
