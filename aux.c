/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:13:31 by binary            #+#    #+#             */
/*   Updated: 2024/12/22 00:41:23 by binary           ###   ########.fr       */
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

void    print_action(t_philo *phil, int action)
{
	pthread_mutex_lock(&phil->info->m_print);
    if (action == FORK)
   		printf("%d has taken a fork\n", phil->id);
	else if (action == EAT)
		printf("%d is eating\n", phil->id);
	else if (action == SLEEP)
		printf("%d is sleepin\n", phil->id);
	else if (action == THINK)
		printf("%d is thinking\n", phil->id);
	else if (action == DEAD)
		printf("%d died\n", phil->id);
	pthread_mutex_unlock(&phil->info->m_print);
}

void ft_putstr(char *str, int fd)
{
    write(fd, str, ft_strlen(str));
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);   
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