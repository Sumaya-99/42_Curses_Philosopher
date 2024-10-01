/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhelal <suhelal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:39:33 by suhelal           #+#    #+#             */
/*   Updated: 2024/09/06 09:13:08 by suhelal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_main *main)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&main->printf_lock);
	pthread_mutex_destroy(&main->dead_lock);
	pthread_mutex_destroy(&main->eating_lock);
	while (i < main->no_philo)
	{
		pthread_mutex_destroy(&main->fork[i]);
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0 && philo->no_philo != 1)
		sleep_time(50);
	while (!dead_end(philo))
	{
		if (eating(philo))
			return (NULL);
		sleeping(philo, philo->time_to_sleep);
		thinking(philo);
	}
	return (arg);
}

int	monitor_join_thread(t_main *main, t_philo *philo, int num_of_philo)
{
	int	i;

	while (1)
	{
		if (check_meal_count(philo, main) || check_dead(main, philo))
			break ;
		usleep(1000);
	}
	i = 0;
	while (i < num_of_philo)
	{
		if (pthread_join(philo[i].t_id, NULL) != 0)
		{
			destroy_mutexes(main);
			write(2, "Pthread joining Error\n", 23);
			return (1);
		}
		i++;
	}
	destroy_mutexes(main);
	return (0);
}

void	create_philo(t_main *main, t_philo *philo, int num_of_philo)
{
	int	i;

	i = 0;
	while (i < num_of_philo)
	{
		if (pthread_create(&philo[i].t_id, NULL, &routine, &philo[i]) != 0)
		{
			destroy_mutexes(main);
			write(2, "Pthread creation Error\n", 24);
			return ;
		}
		i++;
	}
	if (monitor_join_thread(main, philo, num_of_philo))
		return ;
}
