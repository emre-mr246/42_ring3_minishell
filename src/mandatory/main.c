/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/08/09 14:58:17 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../lib/libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

void ft_exit(int exit_code)
{
	rl_clear_history();
	exit(exit_code);
}

static char *create_prompt(t_shell *shell)
{
	char	*prompt;
	char	*tmp;

	prompt = ft_strjoin("\033[1;31mRaRe\033[0m$:\033[1;34m", get_env_value(shell->env, "PWD"));
	tmp = prompt;
	prompt = ft_strjoin(tmp, "\033[0m$ ");
	free(tmp);
	return (prompt);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_shell		*shell;

// 	shell = init_shell(env);
// 	if (!shell)
// 		return (-1);
// 	while (1)
// 	{
// 		shell->line = readline(create_prompt(shell));
// 		if (!shell->line)
// 		{
// 			free(shell->line); // bakılacak
// 			continue ;
// 		}
// 		add_history(shell->line);
// 		shell->tokens = tokenizer(shell->line, shell->env);
// 		if (!shell->tokens)
// 			continue ;
// 		shell->cmd = create_cmd(*(shell->tokens));
// 		if(ft_strncmp(shell->cmd->arr[0], "exit", higher_len(shell->cmd->arr[0], "exit")) == 0)
//         	ft_exit(EXIT_SUCCESS);
// 		update_cmdarr(shell);
// 		print_cmd(shell);
// 		dollar_sign(shell);
// 		execute_cmd(shell);
// 	}
// 	ft_exit(0);
// }

int main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	char	*readline_input;
	char	**arg_input;
	int		i;

	shell = init_shell(envp);
	if (!shell)
		return (-1);
	if (argc == 3 && ft_strncmp(argv[1], "-c", higher_len(argv[1], "-c")) == 0 && argv[2])
	{
		arg_input = ft_split(argv[2], ';');
		if (!arg_input)
			exit(1);
		i = 0;
		while (arg_input[i])
		{
			shell->line = arg_input[i];
			shell->tokens = tokenizer(shell->line, shell->env);
			if (!shell->tokens)
				continue ;
			shell->cmd = create_cmd(*(shell->tokens));
			if(ft_strncmp(shell->cmd->arr[0], "exit", higher_len(shell->cmd->arr[0], "exit")) == 0)
				ft_exit(EXIT_SUCCESS);
			update_cmdarr(shell);
			//print_cmd(shell);
			dollar_sign(shell);
			execute_cmd(shell);
			i++;
		}
	}
	else
	{
		while (1)
		{
			shell->line = readline(create_prompt(shell));
			if (!shell->line)
			{
				// free(shell->line); // bakılacak
				continue ;
			}
			add_history(shell->line);
			shell->tokens = tokenizer(shell->line, shell->env);
			if (!shell->tokens)
				continue ;
			shell->cmd = create_cmd(*(shell->tokens));
			if(ft_strncmp(shell->cmd->arr[0], "exit", higher_len(shell->cmd->arr[0], "exit")) == 0)
				ft_exit(EXIT_SUCCESS);
			update_cmdarr(shell);
			//print_cmd(shell);
			dollar_sign(shell);
			execute_cmd(shell);
		}
	}
	// Free data and exit minishell when done

}