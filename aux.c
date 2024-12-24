/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:13:31 by binary            #+#    #+#             */
/*   Updated: 2024/12/24 16:28:24 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int    get_time(void)
{
    struct timeval  t;
    long int        time;

    if (gettimeofday(&t, NULL) == ERROR)
    {
        handle_error(ERR_TIME);
        return (EXIT_FAILURE);
    }
    time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
    return (time);
}

/* se puede abreviar */
void    print_action(t_philo *phil, int action)
{
	long int	time;

	// printf("ENTRA EN PRINT ACTION\n");
	time = get_time() - phil->info->time_start;
	if(pthread_mutex_lock(&phil->info->m_print))
	{
        printf("ERROR: No se pudo bloquear el mutex de impresión\n");
        return;
    }
    else if (action == FORK)
   		printf("%ld %d has taken a fork\n", time, phil->id);
	else if (action == EAT)
		printf("%ld %d is eating\n", time, phil->id);
	else if (action == SLEEP)
		printf("%ld %d is sleeping\n", time, phil->id);
	else if (action == THINK)
		printf("%ld %d is thinking\n", time, phil->id);
	else if (action == DEAD)
		printf("%ld %d died\n", time, phil->id);
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
}