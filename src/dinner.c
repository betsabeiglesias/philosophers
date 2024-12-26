/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:17:03 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/26 16:09:41 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *arg)
{
	t_philo *phil;

	phil = (t_philo *)arg;
	while (!check_someonedead(phil->info))
	{	
		if ((check_allfull(phil->info)))
			break;
		if(philo_life(phil))
			break;
	}
	return (NULL);
}

int	one_philo(t_philo *phil)
{
	print_action(phil, FORK);
	while (1)
	{
		if (check_someonedead(phil->info))
		{
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int philo_life(t_philo *phil)
{
	if (phil->info->nb_philo == 1)
		if(one_philo(phil))
			return (EXIT_FAILURE);
	if (phil->id % 2 != 0)
		// usleep(100);
		usleep(phil->info->to_eat * 1000 / 2);
	if (philo_dinner(phil))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	philo_dinner(t_philo *phil)
{
	while(!check_someonedead(phil->info) || check_allfull(phil->info))
	{
		if (eating(phil) == EXIT_FAILURE)
			break;
		if (sleeping(phil) == EXIT_FAILURE)
			break;
		if (thinking(phil) == EXIT_FAILURE)
			break;
	}
	return (EXIT_SUCCESS);
}

void	unlock_forks(t_philo *phil)
{
	pthread_mutex_unlock(phil->r_fork);
	pthread_mutex_unlock(phil->l_fork);

}

void lock_forks(t_philo *phil)
{
	if (check_someonedead(phil->info))
		return;
	pthread_mutex_lock(phil->r_fork);
	if (check_someonedead(phil->info))
	{
		pthread_mutex_unlock(phil->r_fork);
		return;
	}
	print_action(phil, FORK);
	pthread_mutex_lock(phil->l_fork);
	if (check_someonedead(phil->info))
	{
		pthread_mutex_unlock(phil->l_fork);
		pthread_mutex_unlock(phil->r_fork);
		return;
	}
	print_action(phil, FORK);
}

int	eating(t_philo *phil)
{
	if(check_someonedead(phil->info) || check_allfull(phil->info))
		return (EXIT_FAILURE) ;
	lock_forks(phil);
	if (check_someonedead(phil->info))
    {
        unlock_forks(phil);
        return (EXIT_FAILURE);
    }
	print_action(phil, EAT);
	pthread_mutex_lock(&phil->info->m_state);
	phil->state = EAT;
	pthread_mutex_unlock(&phil->info->m_state);
	usleep(phil->info->to_eat * 1000);
	pthread_mutex_lock(&phil->info->m_meals);
	phil->last_meal = get_time();
	pthread_mutex_unlock(&phil->info->m_meals);
	unlock_forks(phil);
	if (phil->info->must_meals > 0 && phil->meals_eaten < phil->info->must_meals)
		phil->meals_eaten++;
	count_meals_eaten(phil);
	return (EXIT_SUCCESS);
}

int	sleeping(t_philo *phil)
{
	if(check_someonedead(phil->info) || check_allfull(phil->info))
		return (EXIT_FAILURE);
	print_action(phil, SLEEP);
	usleep(phil->info->to_sleep * 1000);
	pthread_mutex_lock(&phil->info->m_state);
	phil->state = SLEEP;
	pthread_mutex_unlock(&phil->info->m_state);
	return (EXIT_SUCCESS);
}

int	thinking(t_philo *phil)
{
	if(check_someonedead(phil->info) || check_allfull(phil->info))
		return (EXIT_FAILURE) ;
	print_action(phil, THINK);
	pthread_mutex_lock(&phil->info->m_state);
	phil->state = THINK;
	pthread_mutex_unlock(&phil->info->m_state);
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


int	count_meals_eaten(t_philo *phil)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while(i < phil->info->nb_philo)
	{
		pthread_mutex_lock(&phil->info->m_meals); 
		if (phil->info->must_meals != -1 &&  phil->info->phil[i].meals_eaten == phil->info->must_meals)
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