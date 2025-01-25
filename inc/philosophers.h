/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:22:55 by beiglesi          #+#    #+#             */
/*   Updated: 2025/01/25 13:19:58 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

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

# define FORK		"has taken a fork"
# define EAT		"is eating"
# define SLEEP		"is sleeping"
# define THINK		"is thinking"
# define DEAD		"died"

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
	bool			full;
	t_philo			*phil;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_meals;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_state;
}			t_data;	

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long int		last_meal;
	pthread_t		philo;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_data			*info;
}				t_philo;

/* MAIN */
int			get_args(int argc, char **argv, t_data *info);
void		init_philo(t_data *info);
int			init_threads(t_data *info);

/* MUTEX */
int			init_mutex(t_data *info);
int			destroy_mutex(t_data *info);
void		unlock_forks(t_philo *phil);
void		lock_forks(t_philo *phil);

/* DINNER */
void		*routine(void *arg);
int			one_philo(t_philo *philo);
int			philo_dinner(t_philo *phil);
int			philo_life(t_philo *phil);

/* ACTIONS */
int			eating(t_philo *phil);
int			sleeping(t_philo *phil);
int			thinking(t_philo *phil);
int			count_meals_eaten(t_philo *phil);

/* MONITOR */
void		*monitor(void *arg);
int			is_hungry(t_data *info);
int			check_someonedead(t_data *info);
bool		check_allfull(t_data *info);
int			join_threads(t_data *info);

/* AUXILIAR */
long int	get_time(void);
void		print_action(t_philo *phil, char *action);
void		handle_error(int error_type);
void		frees(t_data *info);
void		ft_free_void(void *arg);

/* PARSE */
int			check_arguments(int argc, char **argv);
int			is_space(char c);
int			ft_isdigit_philo(char **str);
int			ft_atoi_philo(char *str);
int			check_int(int argc, char **argv);

#endif