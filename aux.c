/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:13:31 by binary            #+#    #+#             */
/*   Updated: 2024/12/20 21:49:19 by binary           ###   ########.fr       */
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