/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:05 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/27 14:49:01 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_data;

void	ft_dump(void)
{
	if (g_data.i == g_data.len * 8 + 40)
	{
		ft_putstr(g_data.str);
		kill(g_data.si_pid, SIGUSR1);
	}
	g_data.i = 0;
	g_data.j = 0;
	g_data.len = 0;
	g_data.octet = 0;
	if (g_data.free_flag == 1)
		free(g_data.str);
	g_data.free_flag = 0;
}

void	ft_store_str(void)
{
	if (g_data.i == 40)
	{
		g_data.str = malloc((g_data.len + 1) * sizeof(char));
		if (!g_data.str)
			exit(-1);
		g_data.free_flag = 1;
	}
	if (g_data.octet == 0)
	{
		ft_dump();
		return ;
	}
	g_data.str[g_data.j++] = g_data.octet;
	g_data.octet = 0;
}

void	ft_handle_sig(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;
	if (g_data.si_pid != info->si_pid)
	{
		if (g_data.free_flag == 1)
			ft_dump();
		g_data.si_pid = info->si_pid;
	}
	g_data.octet = g_data.octet << 1;
	if (sig == SIGUSR2)
		g_data.octet += 1;
	g_data.i++;
	if (g_data.i == 32)
	{
		g_data.len = g_data.octet;
		g_data.octet = 0;
	}
	else if (g_data.i > 32 && g_data.i % 8 == 0)
		ft_store_str();
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_sigaction = &ft_handle_sig;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	ft_putnbr(pid);
	write(1, "\n", 1);
	while (1)
		pause();
}
