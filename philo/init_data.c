/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhelal <suhelal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:53:01 by suhelal           #+#    #+#             */
/*   Updated: 2024/09/06 09:13:15 by suhelal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork(t_main *main, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&main->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&main->eating_lock, NULL);
	pthread_mutex_init(&main->dead_lock, NULL);
	pthread_mutex_init(&main->printf_lock, NULL);
}

void	init_philo(t_philo *philo, t_main *main, char **av, int i)
{
	philo[i].id = i + 1;
	philo[i].no_meal = main->meal_count;
	philo[i].meal_count = 0;
	philo[i].main = main;
	philo[i].eating = 0;
	philo[i].time_to_die = ft_atoi(av[2]);
	philo[i].time_to_eat = ft_atoi(av[3]);
	philo[i].time_to_sleep = ft_atoi(av[4]);
	philo[i].no_meal = 0;
	if (av[5])
		philo[i].no_meal = ft_atoi(av[5]);
	philo[i].printf_lock = &main->printf_lock;
	philo[i].eating_lock = &main->eating_lock;
	philo[i].dead_lock = &main->dead_lock;
	philo[i].start_time = get_current_time();
	philo[i].last_meal = get_current_time();
	philo[i].no_philo = main->no_philo;
}

void	init_philo_forks(t_philo *philo, pthread_mutex_t *fork, int num, int i)
{
	pthread_mutex_t	*temp;

	philo[i].r_fork = i;
	if (i == 0)
		philo[i].l_fork = num - 1;
	else
		philo[i].l_fork = i - 1;
	philo[i].left_fork = &fork[philo[i].l_fork];
	philo[i].right_fork = &fork[philo[i].r_fork];
	if (philo[i].left_fork > philo[i].right_fork)
	{
		temp = philo[i].left_fork;
		philo[i].left_fork = philo[i].right_fork;
		philo[i].right_fork = temp;
	}
}

void	init_data(t_philo *philo, t_main *main, char **av,
pthread_mutex_t *fork)
{
	int	i;
	int	num;

	i = 0;
	num = main->no_philo;
	init_fork(main, num);
	main->dead = 0;
	while (i < num)
	{
		main->greedy_forks[i] = 0;
		i++;
	}
	i = 0;
	while (i < num)
	{
		init_philo(philo, main, av, i);
		init_philo_forks(philo, fork, num, i);
		i++;
	}
}
