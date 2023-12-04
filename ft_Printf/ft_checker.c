/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:23:16 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/10/30 12:23:20 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_checker(const char *str, int i, va_list arg, int *counter)
{
	if (str[i + 1] == 'c')
		ft_putchar(va_arg(arg, int), counter);
	else if (str[i + 1] == 's')
		ft_putstr(va_arg(arg, char *), counter);
	else if (str[i + 1] == 'p')
		ft_puthexa(va_arg(arg, unsigned long), 'p', counter);
	else if (str[i + 1] == 'd')
		ft_putnbr(va_arg(arg, int), counter);
	else if (str[i + 1] == 'i')
		ft_putnbr(va_arg(arg, int), counter);
	else if (str[i + 1] == 'u')
		ft_putunbr(va_arg(arg, unsigned int), counter);
	else if (str[i + 1] == 'x')
		ft_puthexa(va_arg(arg, unsigned int), 'x', counter);
	else if (str[i + 1] == 'X')
		ft_puthexa(va_arg(arg, unsigned int), 'X', counter);
	else if (str[i + 1] == '%')
		ft_putchar('%', counter);
	else
		ft_putchar(str[i], counter);
}
