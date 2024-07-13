/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/07/10 23:59:50 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../lib/libft/libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include <stdlib.h>

void	listen_input(t_shell *shell)
{
	ft_putstr_fd("RaRe$ ", 1);
	shell->line = get_next_line(shell->std_input);
	while (shell->line)
	{
		ft_putstr_fd("RaRe$ ", 1);
		free(shell->line);
		shell->line = get_next_line(shell->std_input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell		*shell;
	t_tokens	*tokens;

	shell = init_shell(env);
	listen_input(shell);
	if (!shell)
		return (-1);
	shell->tokens = tokenizer(*av, shell->env);
	return (0);
}
