/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:05 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/18 11:30:57 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"



void	ft_decode(int sig)
{
	if (sig == 12)
	{
		write(1, "1", 1);
	}
	else
	{
		write(1, "0", 1);
	}
}

int main()
{
	struct sigaction sa1 = { 0 };
	sa1.sa_handler = &ft_decode;
	sigaction(SIGUSR1, &sa1, NULL);
	struct sigaction sa2 = { 0 };
	sa2.sa_handler = &ft_decode;
	sigaction(SIGUSR2, &sa2, NULL);
	
	int pid;
	
	pid = getpid();
	ft_putnbr(pid);
	write(1, "\n", 1);
	while(1)
	;
}