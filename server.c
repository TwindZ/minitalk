/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:05 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/20 17:34:08 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_data
{
	int octet;
	int len;
	int dataindex;
	char *str;
}				t_data;

void	ft_decode(int bit, t_data *data)
{
	static int	i;
	// static int	j;
	static int 	k;
	static char *str;
	unsigned char c;
	
	data->octet = data->octet * 2;
	data->octet = data->octet + bit;
	k++;
	i++;
	if(k == 32 && i == 32)
	{
		data->len = data->octet;
		ft_putnbr(data->len);
		data->octet = 0;
		i = 0;
	}
	else if(k > 32 && i == 8)
	{
		if(!str)
			// str = malloc((data->len + 1) * sizeof(char));
		if(data->octet == 0)
		{
			// ft_putstr(str);
			data->dataindex = 0;
			i = 0;
			k = 0;
			// free(str);
		}
		c = data->octet;
		// str[j] = c;
		// j++;
		write(1, &c, 1);
		data->octet = 0;
		i = 0;
	}	
}

void	ft_handle_sig(int sig)
{
	t_data data;
	
	if (sig == SIGUSR2)
	{
		// write(1, "1", 1);
		ft_decode(1, &data);
	}
	else
	{
		// write(1, "0", 1);
		ft_decode(0, &data);
	}
}

int main()
{
	struct sigaction sa = { 0 };
	sa.sa_handler = &ft_handle_sig;
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