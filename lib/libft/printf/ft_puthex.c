/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:52:53 by emgul             #+#    #+#             */
/*   Updated: 2024/05/04 17:06:11 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>
#include <stdint.h>

int	ft_hexlen(unsigned	int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	ft_print_hexadecimal(unsigned int num, t_format *f)
{
	if (num >= 16)
	{
		ft_print_hexadecimal(num / 16, f);
		ft_print_hexadecimal(num % 16, f);
	}
	else
	{
		if (num <= 9)
			ft_putchar(num + '0');
		else
		{
			if (f->specifier == 'x')
				ft_putchar(num - 10 + 'a');
			if (f->specifier == 'X')
				ft_putchar(num - 10 + 'A');
		}
	}
}

void	ft_puthex(unsigned int num, t_format *f)
{
	if (num == 0)
		f->printed_chars += write(1, "0", 1);
	else
		ft_print_hexadecimal(num, f);
	f->printed_chars += ft_hexlen(num);
}
