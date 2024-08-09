/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:52:47 by emgul             #+#    #+#             */
/*   Updated: 2024/08/09 15:57:08 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../lib/libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	print_error(char *str, char *cmd, int mode)
{
	if (mode == ENV_NAME)
	{
		ft_putstr_fd("RaRe: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
	}
	else if (mode == CD_NODIR)
	{
		ft_putstr_fd("RaRe: cd: no such file or directory: ", 2);
		ft_putendl_fd(str, 2);
	}
	else if (mode == CD_PWD)
	{
		ft_putstr_fd("RaRe: cd: string not in pwd: ", 2);
		ft_putendl_fd(str, 2);
	}
	else if (mode == NO_CMD)
	{
		ft_putstr_fd("RaRe: command not found: ", 2);
		ft_putendl_fd (str, 2);
	}
}