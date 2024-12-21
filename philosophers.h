/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:22:55 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/21 23:45:12 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>


# define ERR_ARGS	1
# define ERR_NEG	2
# define ERR_MAX	3
# define ERR_TIME	4
# define ERR_MALL	5
# define ERR_THR	6
# define ERR_PHILO	7
# define ERR_MUT	8


# define ERR_MSG_ARG	"Incorrect arguments\n"
# define ERR_MSG_NEG	"Arguments must be >0\n"
# define ERR_MSG_MAX	"Arguments not be exceed INT_MAX\n"
# define ERR_MSG_TIME	"Error getting time\n"
# define ERR_MSG_MALL	"ERROR MALLOC"
# define ERR_MSG_THR	"ERROR CREATING THREAD"
# define ERR_MSG_PHILO	"ERROR INITIALIZING PHILO"
# define ERR_MSG_MUT	"ERROR INITIALIZING MUTEX"

# define ERROR		-1

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				must_meals;
	long int		time_start;
	bool			philo_dead;
	t_philo			*phil;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_meals;
	pthread_mutex_t	m_print;



}			t_data;	

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	bool			alive;
	long int		last_meal;
	t_state			state;
	pthread_t		philo;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	t_data			*info;
}				t_philo;

typedef enum e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
	BIRTH
}			t_state;



/* MAIN */
int			get_args(int argc, char **argv, t_data *info);
int			init_philo(t_data *info);
int			init_mutex(t_data *info);
int			init_threads(t_philo *phil, t_data *info);

/* DINNER */
void	routine(void *arg);
void	dinner_start (t_philo *phil);
void	philo_life(t_philo *phil);
void    print_action(t_philo *phil, int action);



/* AUXILIAR */
void		handle_error(int error_type);
void ft_putstr(char *str, int fd);
int ft_strlen(char *str);

long int	get_time(void);


/* PARSE */
int		check_arguments(int argc, char **argv);
int		is_space(char c);
int		ft_isdigit_philo(char **str);
int 	ft_atoi_philo(char *str);
int		check_int (int argc, char **argv);

#endif