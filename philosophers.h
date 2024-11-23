/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:22:55 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/23 12:24:03 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>


# define ERR_ARGS 1
# define ERR_NEG 2
# define ERR_MAX 3


# define ERR_MSG_ARG "Incorrect arguments\n"
# define ERR_MSG_NEG "Arguments must be >0\n"
# define ERR_MSG_MAX "Arguments not be exceed INT_MAX\n"

typedef struct s_data
{
	int	nb_philo;
	int	to_die;
	int	to_eat;
	int	to_sleep;
	int	must_meals;

}	t_data;	


typedef struct s_philo
{
	int				id;
	pthread_t		philo;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	t_data			*info;
	int				meals_eaten;
};

int main (int argc, char **argv);

/* AUXILIAR */
void	handle_error(int error_type);


/* PARSE */
int	check_arguments(int argc, char **argv);
int	is_space(char c);
int	ft_isdigit_philo(char **str);
int ft_atoi_philo(char *str);
int	negative_args(char **argv);
int	check_int (int argc, char **argv);

#endif