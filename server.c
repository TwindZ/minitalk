/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:05 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/22 16:46:13 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data g_data;

void	ft_handle_sig(int sig, siginfo_t *info, void *ucontext)
{
	static int	i;
	static int	j;
	static int len;
	(void) info;
	(void) ucontext;
	
	if(sig == SIGTERM)
	{
		ft_putstr("\nClosing server...\n\n");
		sleep(3);
		exit(0);
	}	
	g_data.octet = g_data.octet << 1;
	if (sig == SIGUSR2)
		g_data.octet += 1;
	i++;
	if(i == 32)
	{
		len = g_data.octet;
		g_data.octet = 0;
	}
	else if(i > 32 && i % 8 == 0)
	{
		if(i == 40)
		{
			g_data.str = malloc((len + 1) * sizeof(char));
			if(!g_data.str)
				return;
		}
		if(g_data.octet == 0)
		{
			ft_putstr(g_data.str);
			kill(info->si_pid, SIGUSR1);
			i = 0;
			j = 0;
			len = 0;
			free(g_data.str);
			return;
		}
		g_data.str[j++] = g_data.octet;
		g_data.octet = 0;
	}	
}

int main()
{
	
	struct sigaction sa = { 0 };
	sa.sa_sigaction = &ft_handle_sig;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	
	
	int pid;
	
	pid = getpid();
	ft_putnbr(pid);
	write(1, "\n", 1);
	while(1)
		;
}