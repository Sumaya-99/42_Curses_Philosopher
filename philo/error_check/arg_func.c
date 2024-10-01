/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhelal <suhelal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:04:19 by suhelal           #+#    #+#             */
/*   Updated: 2024/03/15 14:13:16 by suhelal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_for_overflow(long long result, int sign, char a)
{
	if (sign == 1)
	{
		if ((result == LLONG_MAX / 10 && a > '7') || result > LLONG_MAX / 10)
			return (-1);
	}
	else if (sign == -1)
	{
		if ((result == LLONG_MAX / 10 && a > '8') || result > LLONG_MAX / 10)
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;
	int		of;

	sign = 1;
	result = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		of = check_for_overflow(result, sign, *str);
		if (of != 1)
			return (of);
		result = result * 10 + *str - '0';
		str++;
	}
	return ((result * sign));
}

int	check_arg(int c, char **av)
{
	int	count;
	int	a;

	count = 1;
	while (count < c)
	{
		a = 0;
		if (!av[count][0])
		{
			write(2, "Error: Empty argument\n", 23);
			return (1);
		}
		if (av[count][0] == ' ')
		{
			while (av[count][a] == ' ')
				a++;
			if (av[count][a] == '\0')
			{
				write(2, "Error: There is empty argument\n", 32);
				return (1);
			}
		}
		count++;
	}
	return (0);
}

void	free_str(char *str)
{
	if (str != NULL)
	{
		free (str);
		str = NULL;
	}
}

int	check_arg_range(char **av, char **split)
{
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) <= 0)
		return (ft_free_word(split), write(2, "Philo number is invalid\n", 25));
	if (ft_atoi(av[2]) <= 60)
		return (ft_free_word(split), write(2, "Time to die is invalid\n", 24));
	if (ft_atoi(av[3]) <= 60)
		return (ft_free_word(split), write(2, "Time to eat is invalid\n", 24));
	if (ft_atoi(av[4]) <= 60)
		return (ft_free_word(split),
			write(2, "Time to sleep is invalid\n", 26));
	if (av[5])
	{
		if (ft_atoi(av[5]) <= 0)
			return (ft_free_word(split),
				write(2, "Number of meals is invalid\n", 28));
	}
	return (0);
}
