/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:47:44 by arimanuk          #+#    #+#             */
/*   Updated: 2025/06/11 18:32:34 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int g_bit_count = 0;

void	flag_handler(int signal)
{
	(void)signal;
	g_bit_count = 1;
}

int	decimal_to_binary(char c, int pid)
{
	int i;
	int bit;

	printf("%c\n", c);
	i = 7;
	while (i >= 0)
	{
		bit = (c >> i) & 1;
		if (bit == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while(!g_bit_count)
			usleep(100);
		g_bit_count = 0;
		i--;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	y;

	i = 0;
	sign = 1;
	y = 0;
	while ((str[i] >= 9 && str[i] <= 13)
		|| str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		y = (y * 10) + (str[i] - 48);
		i++;
	}
	return (sign * y);
}

void	send_massage(int pid, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		decimal_to_binary(str[i], pid);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int pid = 1;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (kill(pid, 0) == -1)
			printf("Wrong PID\n");
		else
		{
			signal(SIGUSR1, flag_handler);
			send_massage(pid, argv[2]);
		}
	}
	return (0);
}