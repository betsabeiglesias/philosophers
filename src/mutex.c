/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:14:53 by binary            #+#    #+#             */
/*   Updated: 2025/01/25 11:31:53 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

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
	if (pthread_mutex_init(&info->m_state, NULL))
		return (handle_error(ERR_MUT), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	destroy_mutex(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_mutex_destroy(&info->forks[i]))
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

void	unlock_forks(t_philo *phil)
{
	pthread_mutex_unlock(phil->r_fork);
	pthread_mutex_unlock(phil->l_fork);
}

// void	lock_forks(t_philo *phil)
// {
// 	if (check_someonedead(phil->info))
// 		return ;
// 	pthread_mutex_lock(phil->r_fork);
// 	if (check_someonedead(phil->info))
// 	{
// 		pthread_mutex_unlock(phil->r_fork);
// 		return ;
// 	}
// 	print_action(phil, FORK);
// 	pthread_mutex_lock(phil->l_fork);
// 	if (check_someonedead(phil->info))
// 	{
// 		pthread_mutex_unlock(phil->l_fork);
// 		pthread_mutex_unlock(phil->r_fork);
// 		return ;
// 	}
// 	print_action(phil, FORK);
// }
void	lock_forks(t_philo *phil)
{
	if (check_someonedead(phil->info))
		return ;
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(phil->l_fork);
		print_action(phil, FORK);
		pthread_mutex_lock(phil->r_fork);
		print_action(phil, FORK);
	}
	else
	{
		pthread_mutex_lock(phil->r_fork);
		print_action(phil, FORK);
		pthread_mutex_lock(phil->l_fork);
		print_action(phil, FORK);
	}
}