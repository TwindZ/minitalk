/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:05 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/23 15:15:08 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data data;

void	ft_store_str(t_data *data)
{
	if((data->i) == 40)
	{
		data->str = malloc((data->len + 1) * sizeof(char));
		if(!data->str)
			exit(-1);
	}
	if(data->octet == 0)
	{
		ft_putstr(data->str);
		kill(data->si_pid, SIGUSR1);
		data->i = 0;
		data->j = 0;
		data->len = 0;
		free(data->str);
		return;
	}
	data->str[data->j] = data->octet;
	data->octet = 0;
}

void	ft_handle_sig(int sig, siginfo_t *info, void *ucontext)
{
	static t_data data;
	(void) info;
	(void) ucontext;
	
	// if(!data.si_pid)
	// 	data.si_pid = info->si_pid;
	// if(data.si_pid != info->si_pid)
	// {
		
	// }
	data.octet = data.octet << 1;
	if (sig == SIGUSR2)
		data.octet += 1;
	data.i++;
	if(data.i == 32)
	{
		data.len = data.octet;
		data.octet = 0;
	}
	else if(data.i > 32 && data.i % 8 == 0)
	{
		ft_store_str(&data);
		// if(data.i == 40)
		// {
		// 	data.str = malloc((data.len + 1) * sizeof(char));
		// 	if(!data.str)
		// 		exit(-1);
		// }
		// if(data.octet == 0)
		// {
		// 	ft_putstr(data.str);
		// 	kill(info->si_pid, SIGUSR1);
		// 	data.i = 0;
		// 	data.j = 0;
		// 	data.len = 0;
		// 	free(data.str);
		// 	return;
		// }
		// data.str[data.j++] = data.octet;
		// data.octet = 0;
	}	
}

int main()
{
	int pid;
	struct sigaction sa;
	
	sa.sa_sigaction = &ft_handle_sig;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	ft_putnbr(pid);
	write(1, "\n", 1);
	while(1)
		pause();
	}