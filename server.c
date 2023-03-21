/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:05 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/21 17:39:57 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_handle_sig(int sig, siginfo_t *info, void *ucontext)
{
	static int	i;
	static int	j;
	static int octet;
	static int len;
	static char *str;
	(void) info;
	(void) ucontext;
	
	octet = octet * 2;
	if (sig == SIGUSR2)
		octet += 1;
	i++;
	if(i == 32)
	{
		len = octet;
		octet = 0;
	}
	else if(i > 32 && i % 8 == 0)
	{
		if(i == 40)
		{
			str = malloc((len + 1) * sizeof(char));
			if(!str)
				return;
		}
		if(octet == 0)
		{
			ft_putstr(str);
			i = 0;
			j = 0;
			len = 0;
			free(str);
			return;
		}
		str[j++] = octet;
		octet = 0;
	}	
}

int main()
{
	
	struct sigaction sa = { 0 };
	sa.sa_sigaction = &ft_handle_sig;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	
	int pid;
	
	pid = getpid();
	ft_putnbr(pid);
	write(1, "\n", 1);
	while(1)
		;
}