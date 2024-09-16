/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/09/16 15:22:57 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>

static char	*create_prompt(t_shell *shell)
{
	char	*prompt;
	char	*tmp;

	prompt = ft_strjoin("\033[1;31mRaRe\033[0m:\033[1;34m",
			get_env_value(shell->env, "PWD"));
	tmp = prompt;
	prompt = ft_strjoin(tmp, "\033[0m$ ");
	free(tmp);
	return (prompt);
}

void	main_loop(t_shell *shell, int tester, char **arg_input, int *i)
{	
	char	*prompt;
	
	prompt = create_prompt(shell);
	if (!tester)
	{
		shell->line = readline(prompt);
		free(prompt);
		if (!shell->line)
			return ;
		add_history(shell->line);
	}
	else
		shell->line = arg_input[*i];
	shell->tokens = tokenizer(shell->line, shell->env);
	if (!shell->tokens)
		return ;
	shell->cmd = create_cmds(shell, shell->tokens);
	parse_cmds(shell);
	//print_cmd(shell);
	execute_cmd(shell);
	shell->cmd->is_builtin = false;
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	shell = init_shell(env);
	if (!shell)
		return (-1);
	// while (1)
		main_loop(shell, 0, NULL, NULL);
	ft_exit(shell, *(shell->last_exit_status));
}
