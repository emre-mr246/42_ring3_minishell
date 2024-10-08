/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:52:47 by emgul             #+#    #+#             */
/*   Updated: 2024/09/25 12:40:12 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	error1(char *str, int mode)
{
	if (mode == ERR_ENVNAME)
	{
		ft_putstr_fd("\'", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
	}
	else if (mode == ERR_NODIR)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

static void	error2(t_shell *shell, char *str, int mode)
{
	if (mode == ERR_EXCBUFF)
		ft_putstr_fd("Exceeded buffer size\n", 2);
	else if (mode == ERR_MEMALLOC)
		ft_putstr_fd("Cannot allocate memory\n", 2);
	else if (mode == ERR_NONNUM)
	{
		*(shell->exit_status) = 255;
		ft_putstr_fd("numeric argument required\n", 2);
	}
	else if (mode == ERR_NOPERM)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (mode == ERR_ISDIR)
	{
		*shell->exit_status = 126;
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	else if (mode == ERR_QUOTES)
		ft_putendl_fd("Odd number of quotes", 2);
	else if (mode == ERR_MANYARGS)
		ft_putendl_fd("too many arguments", 2);
}

static void	error3(t_shell *shell, char *str, int mode)
{
	if (mode == ERR_CD_PWD)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(str, 2);
	}
	else if (mode == ERR_NOCMD)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(str, 2);
	}
	else if (mode == ERR_SYNTAX)
	{
		*(shell->exit_status) = 2;
		ft_putendl_fd("syntax error", 2);
	}
}

void	print_error(t_shell *shell, char *str, int mode, int exits)
{
	*(shell->exit_status) = 1;
	ft_putstr_fd("RaRe: ", 2);
	error1(str, mode);
	error2(shell, str, mode);
	error3(shell, str, mode);
	if (exits)
		ft_exit(*(shell->exit_status));
	else
		return ;
}
