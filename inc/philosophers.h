/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:22:55 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/25 23:53:47 by binary           ###   ########.fr       */
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
typedef enum e_state	t_state;

typedef enum e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
	BIRTH
}			t_state;

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
	pthread_mutex_t	m_meals; //mutex para last_meal que proteger al hilo monitor y los hilos filósofos
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_state;
}			t_data;	

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long int		last_meal;
	t_state			state;
	pthread_t		philo;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	t_data			*info;
}				t_philo;





/* MAIN */
int			get_args(int argc, char **argv, t_data *info);
void		init_philo(t_data *info);
int			init_threads(t_data *info);
int			init_mutex(t_data *info);

/* DINNER */
void	*routine(void *arg);
// int	one_philo(t_philo *philo);
void	dinner_start (t_philo *phil);
int		philo_dinner(t_philo *phil);
int		philo_life(t_philo *phil);
int	eating(t_philo *phil);
int		sleeping(t_philo *phil);
int		thinking(t_philo *phil);
// int	check_someonedead(t_philo *phil);
int	check_someonedead(t_data *info);
bool check_philo_dead(t_data *info);
bool	check_allfull(t_data *info);
// int	check_all_full(t_philo *phil);
void	lock_forks(t_philo *phil);
void	unlock_forks(t_philo *phil);
int	count_meals_eaten(t_philo *phil);

/* MONITOR */
void	*monitor(void *arg);
int		join_threads(t_data *info);
int	destroy_mutex(t_data *info);
int	is_hungry(t_data *info);

/* AUXILIAR */
long int    get_time(void);
void    print_action(t_philo *phil, int action);
void		handle_error(int error_type);
void 	frees(t_data *info);
void	ft_free_void(void *arg);


long int	get_time(void);


/* PARSE */
int		check_arguments(int argc, char **argv);
int		is_space(char c);
int		ft_isdigit_philo(char **str);
int 	ft_atoi_philo(char *str);
int		check_int (int argc, char **argv);

#endif