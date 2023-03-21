/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:05 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/21 13:28:29 by emlamoth         ###   ########.fr       */
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
	static int	j;
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
		data->octet = 0;
		i = 0;
	}
	else if(k > 32 && i == 8)
	{
		if(k == 40)
		{
			str = malloc((data->len + 1) * sizeof(char));
			if(!str)
				return;
		}
		if(data->octet == 0)
		{
			ft_putstr(str);
			i = 0;
			k = 0;
			j = 0;
			data->len = 0;
			free(str);
			return;
		}
		c = data->octet;
		str[j] = c;
		j++;
		data->octet = 0;
		i = 0;
	}	
}

void	ft_handle_sig(int sig)
{
	t_data data;
	
	if (sig == SIGUSR2)
		ft_decode(1, &data);
	else
		ft_decode(0, &data);
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