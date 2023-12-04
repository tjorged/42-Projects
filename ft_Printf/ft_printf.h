/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:13:52 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/10/30 14:14:09 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

void		ft_checker(const char *str, int i, va_list arg, int *counter);
void		ft_puthexa(unsigned long nbr, char mode, int *counter);
void		ft_putunbr(unsigned int nbr, int *counter);
void		ft_putnbr(long nbr, int *counter);
void		ft_putchar(char c, int *counter);
void		ft_putstr(char *str, int *counter);
int			ft_printf(const char *str, ...);
#endif
