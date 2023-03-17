/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:07 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/17 17:21:46 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void ft_encode(unsigned int octet, int typesize, int pid)
{
	unsigned int btindex;
	unsigned char bt;
	
	int i

	i = 0;
	btindex = 0;
	while
	{
		while(btindex < 8)
		{
			bt = octet + i;
			bt = bt << btindex;
			bt = bt >> 7; 
			if(bt == 0)
			{
				// kill(pid, SIGUSR1);
				write(1, "0", 1);
			}
			else
			{
				// kill(pid, SIGUSR2);
				write(1, "1", 1);
			}
			btindex++;
		}
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
	struct sigaction sa;
	
	int i;
	
	i = 0;	
	
	if(argc == 3)
	{
		ft_encode(ft_strlen(argv[2]), 32, 12345);
		while(argv[2][i])
		{
			write(1, "\'", 1);
			write(1, &argv[2][i], 1);
			write(1, "\' - ", 4);
			ft_encode(argv[2][i], 8, 12345);
			i++;
		}
	}
}