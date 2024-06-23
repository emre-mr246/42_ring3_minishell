/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:52:50 by emgul             #+#    #+#             */
/*   Updated: 2024/05/21 16:48:58 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdint.h>
#include <unistd.h>
#include <stdarg.h>

int	ft_ptrlen(uintptr_t num)
{
	int	len;

	len = 0;
	while (num)
	{
		num /= 16;
		len++;
	}
	return (len);
}

void	ft_print_pointer(uintptr_t num, t_format *f)
{
	if (num >= 16)
		ft_print_pointer(num / 16, f);
	if ((num % 16) < 10)
		ft_putchar((num % 16) + '0');
	else
		ft_putchar((num % 16) - 10 + 'a');
}

void	ft_putptr(unsigned long long ptr, t_format *f)
{
	f->printed_chars += write(1, "0x", 2);
	if (ptr == 0)
		f->printed_chars += write(1, "0", 1);
	else
	{
		ft_print_pointer(ptr, f);
		f->printed_chars += ft_ptrlen(ptr);
	}
}
