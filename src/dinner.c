/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:17:03 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/26 19:01:03 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	while (!check_someonedead(phil->info))
	{
		if ((check_allfull(phil->info)))
			break ;
		if (philo_life(phil))
			break ;
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

int	philo_life(t_philo *phil)
{
	if (phil->info->nb_philo == 1)
		if (one_philo(phil))
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
	while (!check_someonedead(phil->info) || check_allfull(phil->info))
	{
		if (eating(phil) == EXIT_FAILURE)
			break ;
		if (sleeping(phil) == EXIT_FAILURE)
			break ;
		if (thinking(phil) == EXIT_FAILURE)
			break ;
	}
	return (EXIT_SUCCESS);
}
