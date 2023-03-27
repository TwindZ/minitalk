/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:07 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/27 16:10:32 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_handle_sig(int sig)
{
	if (sig == SIGUSR1)
		ft_putstr("\n\e[32mHouston, touch down !\e[0m\n\n");
	exit(0);
}

static void	ft_encode(unsigned int octets, int typesize, int pid)
{
	while (typesize)
	{
		usleep(50);
		typesize--;
		if ((octets >> typesize & 1) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
	}
}

int	main(int argc, char **argv)
{
	int					serverpid;
	int					i;
	struct sigaction	sa;

	i = 0;
	sa.sa_handler = &ft_handle_sig;
	sigaction(SIGUSR1, &sa, NULL);
	if (argc == 3)
	{
		serverpid = ft_atoi(argv[1]);
		if (kill(serverpid, 0) < 0)
		{
			ft_putstr("\n\e[31mInvalid server PID\e[0m\n\n");
			exit(-1);
		}
		ft_encode(ft_strlen(argv[2]), 32, serverpid);
		while (argv[2][i])
			ft_encode(argv[2][i++], 8, serverpid);
		ft_encode(argv[2][i], 8, serverpid);
		usleep(ft_strlen(argv[2]) * 10000);
		ft_putstr("\n\e[31mHouston, we have a problem...\e[0m\n\n");
	}
	else
		ft_putstr("\e[31mWrong format ./client <server PID> \"<string>\"\e[0m\n");
}
