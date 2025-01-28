/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:56:25 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/28 13:18:57 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all_fds(t_pipex *data)
{
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	close(data->fd[0]);
	close(data->fd[1]);
}

void	setup_pipes(int in_fd, int out_fd, t_pipex *data)
{
	if (dup2(in_fd, STDIN_FILENO) == -1
		|| dup2(out_fd, STDOUT_FILENO) == -1)
	{
		close_data(data);
		exit(EXIT_FAILURE);
	}
	close_all_fds(data);
}

char	**prepare_cmd(char *cmd_str, t_pipex *data)
{
	char	**cmd;

	cmd = ft_split(cmd_str, ' ');
	if (!cmd)
	{
		close_data(data);
		exit(EXIT_FAILURE);
	}
	return (cmd);
}

void	process1(t_pipex *data, char *cmd_str, char **env)
{
	data->cmd = prepare_cmd(cmd_str, data);
	setup_pipes(data->fd[0], data->pipefd[1], data);
	execute_cmd(data, env);
}

void	process2(t_pipex *data, char *cmd_str, char **env)
{
	close(data->pipefd[1]);
	data->cmd = prepare_cmd(cmd_str, data);
	setup_pipes(data->pipefd[0], data->fd[1], data);
	execute_cmd(data, env);
}
