/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:10 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/22 18:21:59 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

typedef struct 	s_data
{
	int 	byte;
	int 	len;
	char 	*str;
	int 	si_pid;
	int		typesize;
	
}				t_data;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int	ft_putnbr(int n);
int	ft_atoi(char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr(char *str);
char	*ft_itoa(int n);
void	*ft_calloc(size_t count, size_t size);

#endif