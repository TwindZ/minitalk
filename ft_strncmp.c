/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:42:34 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/20 09:59:49 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*Compares up to <n> characters of <s1> to those of <s2>. This function starts 
comparing the first character of each string. If they are equal to each other, 
it continues with the following pairs until the characters differ, until a 
terminating null-character is reached, or until num characters match in both 
strings, whichever happens first.*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i != n)
	{
		if ((s1[i] < s2[i]) || (s1[i] > s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	return (0);
}
