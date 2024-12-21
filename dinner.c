/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:17:03 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/22 00:41:17 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine(void *arg)
{
	t_philo *phil;

	phil = (t_philo *)arg;
	dinner_start(phil);
	if (phil->id % 2 != 0)
	while (phil->info->philo_dead)
	{
		philo_life(phil);

	}	

}

void	dinner_start (t_philo *phil)
{
	pthread_mutex_lock(&phil->info->m_meals);
	phil->last_meal = phil->info->time_start;
	pthread_mutex_unlock(&phil->info->m_meals);
}

void	philo_life(t_philo *phil)
{
	if(phil->alive == false || phil->meals_eaten == 0)
		return ;
	pthread_mutex_lock(&phil->r_fork);
	print_action(phil, FORK);
	pthread_mutex_lock(&phil->l_fork);
	print_action(phil, FORK);
	phil->state = EAT;
	print_action(phil, EAT);
	usleep(phil->info->to_eat * 1000);
	phil->last_meal = get_time();
	ptrhead_mutex_unlock(&phil->r_fork);
	ptrhead_mutex_unlock(&phil->l_fork);
	if (phil->meals_eaten > 0)
		phil->meals_eaten--;
	if (sleepin(phil))
		return (EXIT_FAILURE);
	usleep(phil->info->to_sleep * 1000);
	if (thinking(phil))
		return (EXIT_FAILURE);
	return (NULL);
}

int	sleeping(void *arg)
{
	t_philo	*phil;
	
	phil = (t_philo *)arg;
	if (check_continue(phil))
		return (EXIT_FAILURE);
	print_action(phil, SLEEP);
	return (EXIT_SUCCESS);
}

int	thinking(void *arg)
{
	t_philo	*phil;
	
	phil = (t_philo *)arg;
	if (check_continue(phil))
		return (EXIT_FAILURE);
	print_action(phil, SLEEP);
	return (EXIT_SUCCESS);
}

int	check_continue(t_philo *phil)
{
	pthread_mutex_lock(&phil->info->m_dead);
	if (phil->info->philo_dead = true)
	{
		return (EXIT_FAILURE);
		pthread_mutex_unlock(&phil->info->m_dead);
	}
	return (EXIT_SUCCESS);
}