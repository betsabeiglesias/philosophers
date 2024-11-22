/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:22:55 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/22 12:57:35 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define ERR_ARGS 1

# define ERR_MSG_ARG "Incorrect arguments\n"



int main (int argc, char **argv);

/* AUXILIAR */
void	handle_error(int error_type);


/* PARSE */
int	check_arguments(int argc, char **argv);
int	is_space(char c);
int	ft_isdigit_philo(char **str);
int ft_atoi_philo(char *str);

#endif