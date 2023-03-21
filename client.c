/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:07 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/21 17:38:47 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void ft_encode(unsigned int octets, int typesize, int pid)
{
	while(typesize)
	{
		usleep(50);
		typesize--;
		if((octets >> typesize & 1) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
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
			return(1);
		}	
		ft_encode(ft_strlen(argv[2]), 32, serverpid);
		while(argv[2][i])
			ft_encode(argv[2][i++], 8, serverpid);
		ft_encode(argv[2][i], 8, serverpid);
	}
}