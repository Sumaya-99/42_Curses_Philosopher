/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhelal <suhelal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:42:00 by suhelal           #+#    #+#             */
/*   Updated: 2024/09/06 09:13:23 by suhelal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_main	*main;
	int		no_philo;

	if (ac < 5 || ac > 6)
	{
		write(2, "Error: Argument number should be atleast 4 or 5\n", 49);
		return (1);
	}
	main = malloc(sizeof(t_main));
	if (main == NULL)
		return (1);
	if (check_arguments(main, ac, av))
		return (free(main), 1);
	no_philo = main->no_philo;
	main->philo = malloc(no_philo * sizeof(t_philo));
	main->fork = malloc(no_philo * sizeof(pthread_mutex_t));
	main->greedy_forks = (int *)malloc(sizeof(int) * no_philo);
	if (main->philo == NULL || main->fork == NULL)
		return (1);
	init_data(main->philo, main, av, main->fork);
	create_philo(main, main->philo, no_philo);
	free(main->philo);
	free(main->greedy_forks);
	free(main->fork);
	free(main);
}
