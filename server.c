/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:42:17 by arimanuk          #+#    #+#             */
/*   Updated: 2025/06/11 18:16:11 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


void	handler(int num, siginfo_t *info, void *tralya)
{
	static char c;
	static int count;
	
	(void)tralya;

	c = c << 1;
	if (num == SIGUSR1)
		c = c | 1;
	count++;
	if (count == 8)
	{
		ft_printf("%c", c);
		if (c == '\n')
			ft_printf("\n");
		c = 0;
		count = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int main(void)
{
	struct sigaction sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Failed to set SIGUSR1 handler\n");
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Failed to set SIGUSR2 handler\n");
		return (1);
	}

	ft_printf("PID : %d\n", getpid());

	while (1)
		pause();
}