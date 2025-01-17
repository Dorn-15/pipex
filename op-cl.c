/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op-cl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:01:55 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/16 18:43:45 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_files(char *in, char *out, int (*fd)[2])
{
	(*fd)[0] = open(in, O_RDONLY);
	if ((*fd)[0] == -1)
		return (print_err(in), 0);
	(*fd)[1] = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*fd)[1] == -1)
	{
		close((*fd)[0]);
		return (print_err(out), 0);
	}
	return (1);
}

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

void	close_pipes(int *fd, int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd[0]);
	close(fd[1]);
}