/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:17:03 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/24 18:45:57 by binary           ###   ########.fr       */
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
	// while (!check_someonedead(phil) || !check_all_full(phil))
	while (phil->info->philo_dead == false)
	{
		if (philo_life(phil))
			break;
	}
	return (NULL);
}

void	dinner_start (t_philo *phil)
{
	pthread_mutex_lock(&phil->info->m_meals);
	phil->last_meal = get_time();
	printf("Dinner start %ld del philo %d\n", phil->last_meal, phil->id);
	pthread_mutex_unlock(&phil->info->m_meals);
}

int	philo_life(t_philo *phil)
{
	// if(check_someonedead(phil) || check_all_full(phil))
	if(phil->info->philo_dead == false)
		return (EXIT_FAILURE) ;
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(phil->r_fork);
		// printf("%p r.fork en routine\n", phil->r_fork);
		print_action(phil, FORK);
		pthread_mutex_lock(phil->l_fork);
		// printf("%p r.fork en routine\n", phil->l_fork);
		print_action(phil, FORK);
	}
	else // Filósofos impares
	{
		pthread_mutex_lock(phil->l_fork);
		print_action(phil, FORK);
		pthread_mutex_lock(phil->r_fork);
		print_action(phil, FORK);
	}
	print_action(phil, EAT);
	usleep(phil->info->to_eat * 1000);
	pthread_mutex_lock(&phil->info->m_meals);
	phil->last_meal = get_time();
	pthread_mutex_unlock(&phil->info->m_meals);
	pthread_mutex_unlock(phil->r_fork);
	pthread_mutex_unlock(phil->l_fork);
	if (phil->info->must_meals > 0 && phil->meals_eaten < phil->info->must_meals)
		phil->meals_eaten++;
	if (sleeping(phil))
		return (EXIT_FAILURE);
	if (thinking(phil))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	sleeping(t_philo *phil)
{
	// if(check_someonedead(phil) || check_all_full(phil))
	// 	return (EXIT_FAILURE);
	print_action(phil, SLEEP);
	usleep(phil->info->to_sleep * 1000);
	return (EXIT_SUCCESS);
}

int	thinking(t_philo *phil)
{
	// if(check_someonedead(phil) || check_all_full(phil))
	// 	return (EXIT_FAILURE);
	print_action(phil, THINK);
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
		pthread_mutex_lock(&phil->info->m_meals); // protege meales eaten
		if (phil->info->must_meals != -1 &&  phil->info->phil[i].meals_eaten == phil->info->must_meals)
		{
			full++;
		}
		// printf("filósofo %d y sus meals_eaten son %d\n", phil->info->phil[i].id, phil->info->phil[i].meals_eaten);
		// printf("filósofo %d es el %d full \n", phil->info->phil[i].id, full);
		pthread_mutex_unlock(&phil->info->m_meals);
		i++;
		// printf("FULL %d\n", full);
	}
	if (full == phil->info->nb_philo)
	{
		// printf("Están llenos\n");
		return (EXIT_SUCCESS);
	}
	// printf("NO están llenos\n");
	return (EXIT_FAILURE);
}