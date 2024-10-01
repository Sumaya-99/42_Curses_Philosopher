/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhelal <suhelal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:16:27 by suhelal           #+#    #+#             */
/*   Updated: 2024/09/06 09:13:45 by suhelal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	printf_func(philo, "is thinking " THINKING_EMOJI, philo->id);
}

void	sleeping(t_philo *philo, size_t ms)
{
	printf_func(philo, "is sleeping " SLEEPING_EMOJI, philo->id);
	sleep_time(ms);
}

int	one_philo(t_philo *philo)
{
	if (philo->no_philo == 1)
	{
		sleep_time(philo->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	check_greedy(t_philo *philo, t_main *main)
{
	pthread_mutex_lock(philo->eating_lock);
	if (main->greedy_forks[philo->l_fork] == philo->id
		|| main->greedy_forks[philo->r_fork] == philo->id)
	{
		pthread_mutex_unlock(philo->eating_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->eating_lock);
	return (0);
}

int	eating(t_philo *philo)
{
	t_main	*main;

	main = philo->main;
	if (check_greedy(philo, main))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	printf_func(philo, "has taken a fork " FORK_EMOJI, philo->id);
	if (one_philo(philo))
		return (1);
	pthread_mutex_lock(philo->right_fork);
	printf_func(philo, "has taken a fork " FORK_EMOJI, philo->id);
	pthread_mutex_lock(philo->eating_lock);
	philo->eating = 1;
	pthread_mutex_unlock(philo->eating_lock);
	printf_func(philo, "is eating " EATING_EMOJI, philo->id);
	update_value(philo, main);
	sleep_time(philo->time_to_eat);
	pthread_mutex_lock(philo->eating_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->eating_lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}
