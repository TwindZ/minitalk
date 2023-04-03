/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:07 by emlamoth          #+#    #+#             */
/*   Updated: 2023/04/03 15:20:40 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_data	*ft_init_struct(char *str, int server_pid)
{
	static t_data	*data;

	if (!data)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			exit(EXIT_FAILURE);
		data->str = str;
		data->free_flag = 0;
		data->i = 0;
		data->j = 32;
		data->len = ft_strlen(str);
		data->octet = data->len;
		data->si_pid = server_pid;
	}
	return (data);
}

static void	ft_encode(t_data *data)
{
	data->j--;
	if ((data->octet >> data->j & 1) == 0)
		kill(data->si_pid, SIGUSR1);
	else
		kill(data->si_pid, SIGUSR2);
	if (data->j == 0)
	{
		data->j = 8;
		data->octet = data->str[data->i];
		data->i++;
	}
}

static void	ft_sa_handler(int sig)
{
	t_data	*data;

	data = ft_init_struct(NULL, 0);
	if (sig == SIGUSR1 && data->i <= data->len + 1)
		ft_encode(data);
	else if (sig == SIGUSR2)
	{
		ft_putstr("\n\e[32mTransmission successful!\e[0m\n\n");
		free(data);
		data = NULL;
		exit(EXIT_SUCCESS);
	}
}

static void	ft_valid_pid(int pid, int seq)
{
	if (kill(pid, 0) < 0 && seq == 0)
	{
		ft_putstr("\n\e[31mInvalid server PID\e[0m\n\n");
		exit(EXIT_FAILURE);
	}
	if (kill(pid, 0) < 0 && seq == 1)
	{
		ft_putstr("\n\e[31mThe server stopped answering !\e[0m\n\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	t_data				*data;

	sa.sa_handler = &ft_sa_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (argc == 3)
	{
		data = ft_init_struct(argv[2], ft_atoi(argv[1]));
		ft_valid_pid(data->si_pid, 0);
		kill(getpid(), SIGUSR1);
		while (1)
			ft_valid_pid(data->si_pid, 1);
	}
	else
		ft_putstr("\n\e[31mWrong format ./client <PID> \"<string>\"\e[0m\n\n");
}
