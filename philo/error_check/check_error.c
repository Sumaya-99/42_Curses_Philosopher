/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhelal <suhelal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:40:13 by suhelal           #+#    #+#             */
/*   Updated: 2024/09/06 09:13:02 by suhelal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_for_error(char *str)
{
	int	a;

	a = 0;
	while (str[a])
	{
		if ((str[a] == '-' || str[a] == '+') && (!(str[a + 1] >= '0'
					&& str[a + 1] <= '9')))
			return (1);
		if ((str[a] >= 33 && str[a] < 43) || str[a] == 44
			|| (str[a] >= 46 && str[a] <= 47)
			|| (str[a] >= 58 && str[a] <= 126))
			return (1);
		if ((str[a] >= 9 && str[a] <= 13) || (str[a] == '\n'))
			return (1);
		a++;
	}
	a = 0;
	if (((str[a] == '-' || str[a] == '+') && str[a + 1] >= '0'
			&& str[a + 1] <= '9') || (str[a] >= '0' && str[a] <= '9'))
	{
		while (str[a++])
			if ((str[a] == '-' || str[a] == '+'))
				return (1);
	}
	return (0);
}

int	argument_lengths(int c, char **av)
{
	int	total_length;
	int	count;

	total_length = 0;
	count = 1;
	while (count < c)
	{
		total_length += ft_strlen(av[count]);
		count++;
	}
	return (total_length);
}

char	*join_arguments_with_spaces(int c, char **av, int total_length)
{
	char	*joined_str;
	int		count;
	char	*current;
	char	*temp;

	joined_str = (char *)malloc(sizeof(char) * (total_length + 1));
	if (!joined_str)
		return (NULL);
	count = 1;
	current = joined_str;
	while (count < c)
	{
		temp = av[count];
		while (*temp != '\0')
			*current++ = *temp++;
		if (count < c - 1)
		{
			*current = ' ';
			current++;
		}
		count++;
	}
	*current = '\0';
	return (joined_str);
}

char	*join_arg(int c, char **av)
{
	int		total_length;
	char	*joined_str;

	total_length = argument_lengths(c, av);
	total_length += (c - 2);
	joined_str = join_arguments_with_spaces(c, av, total_length);
	if (*joined_str == '\0')
		free_str(joined_str);
	return (joined_str);
}

int	check_data(t_main *main, char **str)
{
	int				b;

	b = 0;
	while (str[b])
	{
		if ((check_for_error(str[b])))
			return (ft_free_str(str), 1);
		b++;
	}
	main->no_philo = ft_atoi(str[0]);
	return (0);
}
