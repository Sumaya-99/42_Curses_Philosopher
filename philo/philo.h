/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhelal <suhelal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:42:12 by suhelal           #+#    #+#             */
/*   Updated: 2024/09/06 09:13:32 by suhelal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define THINKING_EMOJI "🤔"
#define EATING_EMOJI   "🍽️"
#define SLEEPING_EMOJI "😴"
#define FORK_EMOJI     "🍴"
#define DEATH_EMOJI    "💀" 

typedef struct s_main	t_main;

typedef struct s_philo
{
	int				id;
	pthread_t		t_id;
	int				no_meal;
	int				no_philo;
	int				meal_count;
	size_t			start_time;
	size_t			last_meal;
	size_t			time_to_eat;
	int				eating;
	size_t			time_to_die;
	size_t			time_to_sleep;
	pthread_mutex_t	*printf_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*eating_lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				r_fork;
	int				l_fork;
	t_main			*main;
}					t_philo;

typedef struct s_main
{
	int				no_philo;
	int				philo_dead;
	int				meal_count;
	int				dead;
	int				*greedy_forks;
	pthread_mutex_t	printf_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eating_lock;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}					t_main;

/*PARSING*/
int		ft_atoi(const char *str);
char	**split_arg(char const *s);
int		check_arg(int c, char **av);
void	free_str(char *str);
int		check_arguments(t_main *main, int ac, char **av);
char	*join_arg(int c, char **av);
int		check_data(t_main *main, char **str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
void	ft_free_str(char **spl);
void	negative_error(char **str);
int		check_arg_range(char **av, char **split);
void	ft_free_word(char **spl);

/*PHILO CREATE*/
void	init_data(t_philo *philo, t_main *main,
			char **av, pthread_mutex_t *fork);
void	destroy_mutexes(t_main *main);
void	init_args(t_philo *philo, char **av);
void	create_philo(t_main *main, t_philo *philo, int num_of_philo);
size_t	get_current_time(void);
int		sleep_time(size_t ms);
int		eating(t_philo *philo);
void	sleeping(t_philo *philo, size_t ms);
void	thinking(t_philo *philo);
int		check_meal_count(t_philo *philo, t_main *main);
int		philo_dead(t_philo *philo);
int		check_dead(t_main *main, t_philo *philo);
int		dead_end(t_philo *philo);
void	printf_func(t_philo *philo, char *status, int id);
void	update_value(t_philo *philo, t_main *main);