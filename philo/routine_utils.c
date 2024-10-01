/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhelal <suhelal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:13:37 by suhelal           #+#    #+#             */
/*   Updated: 2024/09/06 09:13:37 by suhelal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Error in get_current_time function\n", 36);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	sleep_time(size_t ms)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(500);
	return (0);
}

void	printf_func(t_philo *philo, char *status, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->printf_lock);
	time = get_current_time() - philo->start_time;
	if (!dead_end(philo))
		printf("%zu %d %s\n", time, id, status);
	pthread_mutex_unlock(philo->printf_lock);
}

void	update_value(t_philo *philo, t_main *main)
{
	pthread_mutex_lock(philo->eating_lock);
	philo->last_meal = get_current_time();
	philo->meal_count++;
	main->greedy_forks[philo->l_fork] = philo->id;
	main->greedy_forks[philo->r_fork] = philo->id;
	pthread_mutex_unlock(philo->eating_lock);
	return ;
}
