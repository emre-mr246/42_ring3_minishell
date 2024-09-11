/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:52:47 by emgul             #+#    #+#             */
/*   Updated: 2024/09/11 14:25:58 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void error1(t_shell *shell, char *str, char *cmd, int mode)
{
	if (mode == ERR_ENVNAME)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
	}
	else if (mode == ERR_NODIR)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (mode == ERR_CD_PWD)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(str, 2);
	}
	else if (mode == ERR_NOCMD)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(str, 2);
	}
}

static void error2(t_shell *shell, char *str, char *cmd, int mode)
{
	if (mode == ERR_EXCBUFF)
		ft_putstr_fd("Exceeded buffer size\n", 2);
	else if (mode == ERR_MEMALLOC)
		ft_putstr_fd("Cannot allocate memory\n", 2);
	else if (mode == ERR_NONNUM)
	{
		*(shell->last_exit_status) = 2;
		ft_putstr_fd("Input nonnumeric\n", 2);
	}
	else if (mode == ERR_NOPERM)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Invalid permission\n", 2);
	}
	else if (mode == ERR_ISDIR)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Is directory\n", 2);
	}
	else if (mode == ERR_QUOTES)
		ft_putendl_fd("Odd number of quotes", 2);
}

void	print_error(t_shell *shell, char *str, char *cmd, int mode, int exits)
{
	*(shell->last_exit_status) = 1;
	ft_putstr_fd("RaRe: ", 2);
	error1(shell, str, cmd, mode);
	error2(shell, str, cmd, mode);
	if (exits)
		exit(*(shell->last_exit_status));
	else
		return ;
}
