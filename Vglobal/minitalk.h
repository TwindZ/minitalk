/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:43:10 by emlamoth          #+#    #+#             */
/*   Updated: 2023/03/27 14:45:50 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

typedef struct s_data
{
	char	*str;
	int		free_flag;
	int		i;
	int		j;
	int		len;
	int		octet;
	int		si_pid;
}t_data;

int		ft_atoi(char *str);
void	ft_putnbr(int nb);
void	ft_putstr(char *str);
int		ft_strlen(char *str);

#endif