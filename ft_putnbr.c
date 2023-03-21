/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:41:32 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/21 09:55:54 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putstr(char *str)
{
	while(*str)
		write(1, str++, 1);
}

int	ft_countnb(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_putnbr(int n)
{
	int		s;
	int		nb;
	char	c;

	s = 0;
	nb = n;
	if (nb == -2147483648)
		ft_putstr("-2147483648");
	else if (nb < 0)
	{
		write(1, "-", 1);
		ft_putnbr(nb *= -1);
	}	
	else if (nb < 10)
	{
		c = (nb + 48);
		write(1, &c, 1);
	}
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	if (n < 0)
		s = 1;
	return (ft_countnb(n) + s);
}
