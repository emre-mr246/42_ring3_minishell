/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:12:26 by emgul             #+#    #+#             */
/*   Updated: 2024/05/04 17:06:08 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdarg.h>
#include <stdint.h>
#include <unistd.h>

t_format	*ft_initialize_format(void)
{
	t_format	*format;

	format = (t_format *)malloc(sizeof(t_format));
	if (!format)
		return (NULL);
	format->printed_chars = 0;
	format->specifier_index = 0;
	return (format);
}

int	ft_find_specifier_index(char *input)
{
	char	*valid_symbols;
	int		specifier_index;
	int		i;
	int		j;

	valid_symbols = "0123456789";
	specifier_index = 0;
	i = 1;
	while (input[i] && !ft_strchr("%cspdiuxX", input[i]))
	{
		j = -1;
		while (valid_symbols[++j])
		{
			if (input[i] == valid_symbols[j])
			{
				specifier_index++;
				break ;
			}
		}
		i++;
	}
	return (specifier_index);
}

int	ft_check_specifier(char *input)
{
	char	*specifiers;

	specifiers = "%cspdiuxX";
	if (ft_strchrs(input, specifiers))
		return (1);
	else
		return (0);
}

int	ft_strchrs(char *haystack, char *needles)
{
	int	i;
	int	j;

	i = 0;
	while (haystack[++i])
	{
		j = -1;
		while (needles[++j])
			if (haystack[i] == needles[j])
				return (1);
	}
	return (0);
}

void	ft_print_format(t_format *f, va_list args)
{
	if (f->specifier == '%')
		f->printed_chars += ft_putchar('%');
	else if (f->specifier == 'c')
		f->printed_chars += ft_putchar(va_arg(args, int));
	else if (f->specifier == 's')
		ft_putstr(va_arg(args, char *), f);
	else if (f->specifier == 'p')
		ft_putptr(va_arg(args, unsigned long long), f);
	else if (f->specifier == 'i' || f->specifier == 'd')
		ft_putnbr(va_arg(args, int), f);
	else if (f->specifier == 'u')
		ft_putunsigned(va_arg(args, unsigned int), f);
	else if (f->specifier == 'x' || f->specifier == 'X')
		ft_puthex(va_arg(args, unsigned int), f);
}
