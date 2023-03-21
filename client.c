/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:07 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/21 13:24:56 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void ft_encode(unsigned int octets, int typesize, int pid)
{
	unsigned int btindex;	
	int i;

	i = typesize;
	btindex = 0;

	while(i)
	{
		usleep(30);
		i--;
		if((octets >> i & 1) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		btindex++;
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
	int serverpid;
	int i;
	
	serverpid = ft_atoi(argv[1]);
	i = 0;
	if(argc == 3)
	{
		if(ft_strncmp("&exit", argv[2], 5) == 0)
		{	
			kill(serverpid, SIGTERM);
			return(0);
		}	
		ft_encode(ft_strlen(argv[2]), 32, serverpid);
		while(argv[2][i])
		{
			ft_encode(argv[2][i], 8, serverpid);
			i++;
		}
		ft_encode(argv[2][i], 8, serverpid);
	}
}