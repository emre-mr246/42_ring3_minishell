/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/07/16 13:38:15 by kali             ###   ########.fr       */
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

char	*make_path(char *uncompleted_path, char *cmd)
{
	char	*path_part;
	char	*valid_path;

	path_part = ft_strjoin(uncompleted_path, "/");
	if (!path_part)
		exit(-1);
	valid_path = ft_strjoin(path_part, cmd);
	free(path_part);
	if (access(valid_path, F_OK) < 0)
		return (NULL);
	return (valid_path);
}

char	*find_valid_path(char *cmd, t_env *envp)
{
	int		i;
	char	**paths;
	char	*valid_path;
	char	*tmp;

	while (ft_strnstr(envp->key, "PATH", 4) == 0)
		envp = envp->next;
	paths = ft_split(envp->value, ':');
	if (!paths || !*paths)
		exit(-1);
	free(tmp);
	i = 0;
	while (paths[i])
	{
		valid_path = make_path(paths[i++], cmd);
		if (valid_path != NULL)
			break ;
	}
	// free_array(paths);
	return (valid_path);
}

// void child_process(t_shell *shell, t_tokens *token)
// {
// 	char *path;
// 	int result;

// 	path = find_valid_path(token->token, shell->env);
// 	result = execve(path, shell->, shell->envp);
// 	// if (result == -1)
// 	// 	error("execve failed");
// 	ft_putendl_fd(path, 1);
// 	exit(0);
// }

// void execute_cmd(t_shell *shell, t_tokens *token)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		exit(-1);
// 	if (pid == 0)
// 		child_process(shell, token);
// 	waitpid(-1, NULL, 0);
// }



// t_cmd *parser(t_tokens token)
// {
// 	t_cmd *cmd;
// 	char **commands;
// 	int i;

// 	i = 0;
// 	while (1)
// 	{
// 		handle_ampersand()
// 		commands[i] = token.token;
// 		if (token.next)
// 			token = *token.next;
// 		else
// 			break ;
// 		i++;
// 	}
// 	return (cmd);
// }

int	main(int ac, char **av, char **env)
{
	t_shell		*shell;
	t_cmd 		*cmd;

	shell = init_shell(env);
	if (!shell)
		return (-1);
	while (1)
	{
		ft_putstr_fd("\033[1;31mRaRe\033[0m$ ", 1);
		shell->line = get_next_line(shell->std_input);
		shell->tokens = tokenizer(shell->line, shell->env);
		while (shell->tokens->token)
		{
			printf("token: %s\n", shell->tokens->token);
			shell->tokens = shell->tokens->next;
		}
		// cmd = parser(*(shell->tokens));
		// execute_cmd(shell, tokens);
		free(shell->line);
	}
	return (0);
}
