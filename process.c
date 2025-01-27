/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:56:25 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/23 17:07:00 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process1(int *fd, int *pipefd, char **cmd1, char **env)
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd[0]);
	close(fd[1]);
	execute_cmd(cmd1, env);
}

void	process1(int *fd, int *pipefd, char *cmd_str, char **env)
{
	char	**cmd;

	cmd = ft_split(cmd_str, ' ');
	if (!cmd)
		exit(EXIT_FAILURE);
	child_process1(fd, pipefd, cmd, env);
	free_split(cmd);
	exit(EXIT_FAILURE);
}

void	child_process2(int *fd, int *pipefd, char **cmd2, char **env)
{
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd[0]);
	close(fd[1]);
	execute_cmd(cmd2, env);
}

void	process2(int *fd, int *pipefd, char *cmd_str, char **env)
{
	char	**cmd;

	cmd = ft_split(cmd_str, ' ');
	if (!cmd)
		exit(EXIT_FAILURE);
	child_process2(fd, pipefd, cmd, env);
	free_split(cmd);
	exit(EXIT_FAILURE);
}
