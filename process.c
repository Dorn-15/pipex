/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:56:25 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/22 17:34:31 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process1(int *fd, int *pipefd, char **cmd1, char **env)
{
	if (!fd || !pipefd || !cmd1 || !env)
		exit(EXIT_FAILURE);
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

void	child_process2(int *fd, int *pipefd, char **cmd2, char **env)
{
	if (!fd || !pipefd || !cmd2 || !env)
		exit(EXIT_FAILURE);
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
