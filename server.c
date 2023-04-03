/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:05 by emlamoth          #+#    #+#             */
/*   Updated: 2023/04/03 16:33:34 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_dump(t_data *data)
{
	if (data->i == data->len * 8 + 40)
	{
		kill(data->si_pid, SIGUSR2);
		ft_putstr(data->str);
		ft_putstr("\e[32m\n");
		ft_putnbr(data->i);
		ft_putstr(" bits received !\n\e[33mServer ID : ");
		ft_putnbr(getpid());
		ft_putstr("\n\e[32mReady to receive again !\n\e[0m");
	}
	data->i = 0;
	data->j = 0;
	data->len = 0;
	data->octet = 0;
	if (data->free_flag == 1)
	{
		free(data->str);
		data->str = NULL;
		data->free_flag = 0;
	}
}

static t_data	*ft_init_struct(void)
{
	static t_data	*data;

	if (!data)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			exit(EXIT_FAILURE);
		data->str = NULL;
		data->free_flag = 0;
		data->i = 0;
		data->j = 0;
		data->len = 0;
		data->octet = 0;
		data->si_pid = 0;
	}
	return (data);
}

static void	ft_store_str(t_data *data)
{
	if (data->free_flag == 0)
	{
		data->str = malloc((data->len + 1) * sizeof(char));
		if (!data->str)
			exit(EXIT_FAILURE);
		data->free_flag = 1;
	}
	data->str[data->j++] = data->octet;
	if (data->octet == 0)
	{
		ft_dump(data);
		return ;
	}
	data->octet = 0;
}

static void	ft_sa_sigaction(int sig, siginfo_t *info, void *ucontext)
{
	t_data	*data;

	(void) ucontext;
	data = ft_init_struct();
	if (data->si_pid != info->si_pid && info->si_pid != 0)
	{
		if (data->free_flag == 1)
			ft_dump(data);
		data->si_pid = info->si_pid;
	}
	data->octet = data->octet << 1;
	if (sig == SIGUSR2)
		data->octet |= 1;
	data->i++;
	if (data->i == 32 && data->free_flag == 0)
	{
		data->len = data->octet;
		data->octet = 0;
	}
	else if (data->i > 32 && data->i % 8 == 0)
		ft_store_str(data);
	if (data->i < data->len * 8 + 40)
		kill(data->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &ft_sa_sigaction;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_init_struct();
	ft_putstr("\e[33mServer ID : ");
	ft_putnbr(getpid());
	ft_putstr("\n\e[32mReady to receive !\n\e[0m");
	while (1)
		pause();
	free(ft_init_struct);
}
