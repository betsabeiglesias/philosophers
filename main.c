/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:21:07 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/22 12:21:42 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	printf("empezamos\n");
	if(argc != 5 && argc != 6)
		return(handle_error(ERR_ARGS), EXIT_FAILURE);
	return(EXIT_SUCCESS);

}