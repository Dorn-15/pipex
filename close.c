/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:01:55 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/22 17:34:27 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_prog(int (*fd)[2], char **cmd1, char **cmd2)
{
	if (cmd1)
		free_split(cmd1);
	if (cmd2)
		free_split(cmd2);
	if (fd)
	{
		close((*fd)[0]);
		close((*fd)[1]);
	}
}

void	close_pipes(int *fd, int *pipefd, pid_t pid)
{
	int	status;

	status = 0;
	if (pipefd)
	{
		if (pipefd[0] != -1)
			close(pipefd[0]);
		if (pipefd[1] != -1)
			close(pipefd[1]);
	}
	if (fd)
	{
		if (fd[0] != -1)
			close(fd[0]);
		if (fd[1] != -1)
			close(fd[1]);
	}
	waitpid(pid, &status, 0);
	wait(NULL);
}
