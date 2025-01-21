/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:01:55 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/21 16:07:31 by adoireau         ###   ########.fr       */
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

void	close_pipes(int *fd, int *pipefd, pid_t	pid[2])
{
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (pid)
	{
		waitpid(pid[0], NULL, 0);
		waitpid(pid[1], NULL, 0);
	}
}
