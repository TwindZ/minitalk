/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:05 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/27 17:10:18 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_dump(t_data *data)
{
	if (data->i == data->len * 8 + 40)
	{
		ft_putstr(data->str);
		kill(data->si_pid, SIGUSR1);
	}
	data->i = 0;
	data->j = 0;
	data->len = 0;
	data->octet = 0;
	if (data->free_flag == 1)
	{
		free(data->str);
		// free(data);
	}
	data->free_flag = 0;
}

void	ft_store_str(t_data *data)
{
	if (data->free_flag == 0)
	{
		data->str = malloc((data->len + 1) * sizeof(char));
		if (!data->str)
			exit(-1);
		data->free_flag = 1;
	}
	if (data->octet == 0)
	{
		ft_dump(data);
		return ;
	}
	data->str[data->j++] = data->octet;
	data->octet = 0;
	data->i = 0;
}

t_data	*ft_init_struct(void)
{
	static t_data *data;
	
	if(!data)
	{
		ft_putstr("init");
		data = malloc(sizeof(t_data));
		data->str = NULL;
		data->free_flag = 0;
		data->i = 0;
		data->j = 0;
		data->len = 0;
		data->octet = 0;
		data->si_pid = 0;
	}
	return(data);
}

void	ft_handle_sig(int sig, siginfo_t *info, void *ucontext)
{
	t_data	*data;

	data = ft_init_struct();

	(void) ucontext;
	if (data->si_pid != info->si_pid)
	{
		if (data->free_flag == 1)
			ft_dump(data);
		data->si_pid = info->si_pid;
	}
	data->octet = data->octet << 1;
	if (sig == SIGUSR2)
		data->octet += 1;
	data->i++;
	if (data->i == 32 && data->free_flag == 0)
	{
		data->len = data->octet;
		data->octet = 0;
		data->i = 0;
	}
	else if (data->i == 8 && data->len > 0)
		ft_store_str(data);
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;
	
	sa.sa_sigaction = &ft_handle_sig;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_init_struct();
	pid = getpid();
	ft_putstr("\e[33mServer ID : ");
	ft_putnbr(pid);
	ft_putstr("\n\e[32mReady to receive !\n\e[0m");
	while (1)
		pause();
}
