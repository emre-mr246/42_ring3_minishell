/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 08:03:49 by emgul             #+#    #+#             */
/*   Updated: 2024/05/04 17:06:03 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

int	ft_format_specifier(char *input, va_list args, int *i)
{
	t_format	*f;
	int			printed_chars;

	f = ft_initialize_format();
	if (ft_check_specifier(input))
		f->specifier_index = ft_find_specifier_index(input);
	else
		return (free(f), 0);
	f->specifier = input[f->specifier_index + 1];
	ft_print_format(f, args);
	*i += f->specifier_index + 2;
	printed_chars = f->printed_chars;
	return (free(f), printed_chars);
}

int	ft_printf(const char *input, ...)
{
	int			i;
	va_list		args;
	int			printed_chars;

	if (!input || !*input)
		return (0);
	va_start(args, input);
	i = 0;
	printed_chars = 0;
	while (input[i])
	{
		if (input[i] == '%')
			printed_chars += ft_format_specifier((char *)input + i, args, &i);
		else
			printed_chars += write(1, &input[i++], 1);
	}
	va_end(args);
	return (printed_chars);
}
