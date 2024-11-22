/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:01:50 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/22 13:02:39 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arguments(int argc, char **argv)
{
	if(argc != 5 && argc != 6)
		return(handle_error(ERR_ARGS), EXIT_FAILURE);
	if(ft_isdigit_philo(argv))
		return(handle_error(ERR_ARGS), EXIT_FAILURE);
	return(EXIT_SUCCESS);
}

int	is_space(char c)
{
	if (c == 32 || (c >= 8 && c <= 13))
		return (1);
	return (0);
}

int	ft_isdigit_philo(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(str[i][j] != '\0')
	{
		{
			if(str[i][j] >= '0' && str[i][j] <= '9' || str[i][j] == '-' || str[i][j] == '+')
				return(1);
			j++;
		}
		i++;
	}
	return(0);
}

int ft_atoi_philo(char *str)
{
	int			i;
	int			sign;
	long int	nb;
	
	i = 0;
	sign = 1;
	nb = 0;
	while(is_space(str[i]))
		i++;
	if(str[i] == '-')
		sign = -1;
	if(str[i] == '-' || str[i] == '+')
		i++;
	while(str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return(nb * sign);	
}