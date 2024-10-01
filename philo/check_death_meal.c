/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death_meal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhelal <suhelal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:09:06 by suhelal           #+#    #+#             */
/*   Updated: 2024/09/06 09:09:06 by suhelal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meal_count(t_philo *philo, t_main *main)
{
	int	i;
	int	philo_ate;

	i = 0;
	philo_ate = 0;
	if (philo->no_meal <= 0)
		return (0);
	pthread_mutex_lock(philo->eating_lock);
	while (i < philo->no_philo)
	{
		if (philo[i].meal_count >= philo->no_meal)
			philo_ate++;
		i++;
	}
	pthread_mutex_unlock(philo->eating_lock);
	if (philo_ate == philo->no_philo)
	{
		pthread_mutex_lock(philo->dead_lock);
		main->dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	return (0);
}

int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->eating_lock);
	if (get_current_time() - philo->last_meal >= philo->time_to_die
		&& philo->eating == 0)
	{
		return (pthread_mutex_unlock(philo->eating_lock), 1);
	}
	pthread_mutex_unlock(philo->eating_lock);
	return (0);
}

int	dead_end(t_philo *philo)
{
	t_main	*main;

	pthread_mutex_lock(philo->dead_lock);
	main = philo->main;
	if (main->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

int	check_dead(t_main *main, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->no_philo)
	{
		if (philo_dead(&philo[i]))
		{
			printf_func(philo, "has died " DEATH_EMOJI, philo[i].id);
			pthread_mutex_lock(philo->dead_lock);
			main->dead = 1;
			pthread_mutex_unlock(philo->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}
