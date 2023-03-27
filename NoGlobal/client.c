/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:07 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/27 14:41:15 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_handle_sig(int sig)
{
	if (sig == SIGUSR1)
		ft_putstr("\nHouston, touch down !\n\n");
	exit(0);
}

void	ft_encode(unsigned int octets, int typesize, int pid)
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
			ft_putstr("\nInvalid server PID\n\n");
			exit(-1);
		}
		ft_encode(ft_strlen(argv[2]), 32, serverpid);
		while (argv[2][i])
			ft_encode(argv[2][i++], 8, serverpid);
		ft_encode(argv[2][i], 8, serverpid);
		usleep(ft_strlen(argv[2]) * 1500);
		ft_putstr("\nHouston, we have a problem...\n\n");
	}
	else
		ft_putstr("\nWrong format ./client <server PID> \"<string to send>\"\n\n");
}
