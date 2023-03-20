/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:07 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/18 12:20:22 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void ft_encode(unsigned int octets, int typesize, int pid)
{
	unsigned int btindex;
	unsigned char bt;
	
	int i;

	i = typesize;
	btindex = 0;

		while(i)
		{
			// usleep(30);
			i--;
			if((octets >> i & 1) == 0)
			{
				kill(pid, SIGUSR1);
				write(1, "0", 1);
			}
			else
			{
				kill(pid, SIGUSR2);
				write(1, "1", 1);
			}
			btindex++;
		}
	write(1, "\n", 1);
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
	int serverpid;
	int i;
	
	serverpid = ft_atoi(argv[1]);
	// sleep(10);
	// kill(serverpid, SIGTERM);
	i = 0;
	if(argc == 3)
	{
		ft_encode(ft_strlen(argv[2]), 32, serverpid);
		usleep(5000000);
		while(argv[2][i])
		{
			write(1, "\'", 1);
			write(1, &argv[2][i], 1);
			write(1, "\' - ", 4);
			ft_encode(argv[2][i], 8, serverpid);
			i++;
		}
	}
}