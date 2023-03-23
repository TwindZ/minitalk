/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:05 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/23 12:40:16 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data g_data;

void	ft_handle_sig(int sig, siginfo_t *info, void *ucontext)
{
	// static int	i;
	// static int	j;
	// static int len;
	(void) info;
	(void) ucontext;
		
	if (sig == SIGUSR2 && sig > 0)
	{
	sleep(1);
	kill(info->si_pid, SIGUSR2);
	ft_putstr("send sig2 to : ");
	ft_putnbr(info->si_pid);
	}
	return;
}

int main()
{
	
	struct sigaction sa;
	sa.sa_sigaction = &ft_handle_sig;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	
	
	int pid;
	
	pid = getpid();
	ft_putnbr(pid);
	write(1, "\n", 1);
	while(1)
		sigemptyset(&sa.sa_flags);
}