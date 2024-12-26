/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:01:50 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/26 15:39:06 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	check_arguments(int argc, char **argv)
{
	if(argc != 5 && argc != 6)
		return(handle_error(ERR_ARGS), EXIT_FAILURE);
	if(ft_isdigit_philo(argv))
		return(handle_error(ERR_ARGS), EXIT_FAILURE);
	if(check_int(argc, argv))
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

	i = 1;
	while(str[i])
	{
		j = 0;
		while(is_space(str[i][j]))
			j++;
		if(str[i][j] == '-' || str[i][j] == '+')
			j++;
		while(str[i][j])
		{
			if (str[i][j] < '0' || str[i][j] > '9')
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

int	check_int (int argc, char **argv)
{
	int			i;
	long int	nb;

	i = 1;
	while(i < argc)
	{
		nb = ft_atoi_philo(argv[i]);
		if (nb < 0)
			return(handle_error(ERR_NEG), EXIT_FAILURE);
		if (nb > INT_MAX)
			return(handle_error(ERR_MAX), EXIT_FAILURE);
		i++;
	}
	return(EXIT_SUCCESS);
}