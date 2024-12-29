/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:13:31 by binary            #+#    #+#             */
/*   Updated: 2024/12/29 19:54:15 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long int	get_time(void)
{
	struct timeval	t;
	long int		time;

	if (gettimeofday(&t, NULL) == ERROR)
	{
		handle_error(ERR_TIME);
		return (EXIT_FAILURE);
	}
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time);
}

void	print_action(t_philo *phil, char *action)
{
	long int	time;

	time = get_time() - phil->info->time_start;
	pthread_mutex_lock(&phil->info->m_print);
	printf("%ld %d %s\n", time, phil->id, action);
	pthread_mutex_unlock(&phil->info->m_print);
}

void	handle_error(int error_type)
{
	if (error_type == ERR_ARGS)
		printf(ERR_MSG_ARG);
	if (error_type == ERR_NEG)
		printf(ERR_MSG_NEG);
	if (error_type == ERR_MAX)
		printf(ERR_MSG_MAX);
	if (error_type == ERR_TIME)
		printf(ERR_MSG_TIME);
	if (error_type == ERR_MALL)
		printf(ERR_MSG_MALL);
	if (error_type == ERR_THR)
		printf(ERR_MSG_THR);
	if (error_type == ERR_PHILO)
		printf(ERR_MSG_PHILO);
	if (error_type == ERR_MUT)
		printf(ERR_MSG_MUT);
}

void	frees(t_data *info)
{
	ft_free_void((void *)info->phil);
	ft_free_void((void *)info->forks);
}

void	ft_free_void(void *arg)
{
	if (arg)
		free(arg);
	return ;
}
