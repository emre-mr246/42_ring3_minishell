/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/07/19 18:12:07 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../lib/libft/libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	t_shell		*shell;

	shell = init_shell(env);
	if (!shell)
		return (-1);
	while (1)
	{
		ft_putstr_fd("\033[1;31mRaRe\033[0m$ ", 1);
		shell->line = get_next_line(shell->std_input);
		shell->tokens = tokenizer(shell->line, shell->env);
		shell->cmd = parser(*(shell->tokens));
		execute_cmd(shell);
		free(shell->line);
	}
	return (0);
}
