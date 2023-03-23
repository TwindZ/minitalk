/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:07 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/23 13:23:22 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data g_data;

void	ft_encode(int byte)
{
		g_data.typesize--;
			ft_putnbr(g_data.si_pid);

		// ft_putnbr(byte >> g_data.typesize);
		if((byte >> g_data.typesize & 1) == 0)
		{
			kill(g_data.si_pid, SIGUSR1);
			ft_putstr("0");
		}
		else
		{
			kill(g_data.si_pid, SIGUSR2);
			ft_putstr("1");
		}
}

void	ft_handle_sig(int sig, siginfo_t *info, void *ucontext)
{
	// static int b_count;
	// static int i;
	// ft_putnbr(b_count);
	(void) ucontext;
	(void) info;
		if(sig == SIGUSR1)
		{
			ft_putstr("\nHouston, touch down !\n\n");
			exit(0);
		}
		if(sig == SIGUSR2)
		{

			kill(g_data.si_pid, SIGUSR2);
			ft_putstr("send to : ");
			ft_putnbr(g_data.si_pid);
		}
}

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}

int main(int argc, char **argv)
{
	int i;
	struct sigaction sa;
	sa.sa_sigaction = &ft_handle_sig;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sa.sa_flags = SA_SIGINFO; 
	g_data.si_pid = ft_atoi(argv[1]);
	g_data.typesize = 32;
	g_data.str = argv[
	i = 0;
	if(argc == 3)
	{
		g_data.len = ft_strlen(argv[2]);
		ft_putnbr(getpid());
		kill(getpid(), SIGUSR2);
		wait(&g_data.si_pid);
	}
	else
	{
		ft_putstr("Format must be : ./client <server_pid> <message>\n");
		exit(1);
	}
	// usleep(ft_strlen(argv[2]) * 1500 );
	// ft_putstr("\nHouston, we have a problem...\n\n");
}
