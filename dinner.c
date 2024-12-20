/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:17:03 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/19 21:42:37 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

