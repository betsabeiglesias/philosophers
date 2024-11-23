/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:21:07 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/23 12:30:08 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	printf("empezamos\n");
	if(check_arguments(argc, argv))
		return(EXIT_FAILURE);

	return(EXIT_SUCCESS);

}

int get_args(char **argv, t_data *info)
{
	if(check_arguments(argc, argv))
		return(EXIT_FAILURE);
	info->nb_philo = argv[1];
	info->to_die = argv[2];
	info->to_eat = argv[3];
	info->to_sleep = argv[4];
	if (argv[5])
		info->must_meals = argv[5];
	else
		(void) info->must_meals;
	info->meals_eaten = 0;

}


}