/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:57:04 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/22 16:38:19 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned int		i;
	unsigned char		*str;

	str = (unsigned char *)s;
	i = 0;
	if (!s)
		return (NULL);
	while (i < len)
		str[i++] = c;
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*a;

	a = (malloc(count * size));
	if (!a)
		return (NULL);
	ft_memset(a, 0, count * size);
	return (a);
}
