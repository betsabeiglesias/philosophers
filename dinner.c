/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:17:03 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/22 23:25:55 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo *phil;

	phil = (t_philo *)arg;
	dinner_start(phil);
	// si solo hay un filósofo
	if (phil->id % 2 != 0)
		usleep(100);
	while (!check_someonedead(phil) || !check_all_full(phil))
	{
		if (philo_life(phil))
			break;
	}
	return (NULL);
}

void	dinner_start (t_philo *phil)
{
	pthread_mutex_lock(&phil->info->m_meals);
	phil->last_meal = phil->info->time_start;
	printf("time start del mutex %ld\n", phil->last_meal);
	pthread_mutex_unlock(&phil->info->m_meals);
}

int	philo_life(t_philo *phil)
{
	if(check_someonedead(phil) || check_all_full(phil))
		return (EXIT_FAILURE) ;
	pthread_mutex_lock(phil->r_fork);
	print_action(phil, FORK);
	pthread_mutex_lock(phil->l_fork);
	print_action(phil, FORK);
	// phil->state = EAT;
	print_action(phil, EAT);
	usleep(phil->info->to_eat * 1000);
	phil->last_meal = get_time();
	pthread_mutex_unlock(phil->r_fork);
	pthread_mutex_unlock(phil->l_fork);
	if (phil->meals_toeat > 0)
		phil->meals_toeat--;
	if (sleeping(phil))
		return (EXIT_FAILURE);
	if (thinking(phil))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	sleeping(t_philo *phil)
{
	if(check_someonedead(phil) || check_all_full(phil))
		return (EXIT_FAILURE);
	print_action(phil, SLEEP);
	usleep(phil->info->to_sleep * 1000);
	return (EXIT_SUCCESS);
}

int	thinking(t_philo *phil)
{
	if(check_someonedead(phil) || check_all_full(phil))
		return (EXIT_FAILURE);
	print_action(phil, SLEEP);
	return (EXIT_SUCCESS);
}

int	check_someonedead(t_philo *phil)
{
	pthread_mutex_lock(&phil->info->m_dead);
	if (phil->info->philo_dead == true)
	{
		pthread_mutex_unlock(&phil->info->m_dead);
		return (EXIT_SUCCESS);
	}
	pthread_mutex_unlock(&phil->info->m_dead);
	return (EXIT_FAILURE);
}

int	check_all_full(t_philo *phil)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while(i < phil->info->nb_philo)
	{
		if (phil[i].meals_toeat == 0)
			full++;
		i++;
	}
	if (full == phil->info->nb_philo)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}