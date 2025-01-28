/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:09:14 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/28 13:29:05 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ac_error(int ac)
{
	if (ac < 5)
		ft_putstr_fd("Error: too few arguments\n", 2);
	else
		ft_putstr_fd("Error: too many arguments\n", 2);
	ft_putstr_fd("Expected: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 1);
	return (1);
}

void	close_data(t_pipex *data)
{
	if (data->fd[0] != -1)
		close(data->fd[0]);
	if (data->fd[1] != -1)
		close(data->fd[1]);
	if (data->pipefd[0] != -1)
		close(data->pipefd[0]);
	if (data->pipefd[1] != -1)
		close(data->pipefd[1]);
	if (data->cmd)
		free_split(data->cmd);
	if (data->cmd_path)
		free(data->cmd_path);
	free(data);
}

void	open_files(char *in, char *out, t_pipex *data)
{
	data->fd[0] = open(in, O_RDONLY);
	if (data->fd[0] == -1)
		perror(in);
	data->fd[1] = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd[1] == -1)
	{
		perror(out);
		close_data(data);
		exit(EXIT_FAILURE);
	}
	data->pipefd[0] = -1;
	data->pipefd[1] = -1;
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*data;
	pid_t	pid1;

	if (ac != 5)
		return (ac_error(ac));
	data = malloc(sizeof(t_pipex));
	open_files(av[1], av[4], data);
	if (pipe(data->pipefd) == -1)
	{
		close_data(data);
		return (perror("pipe"), 1);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		close_data(data);
		return (perror("fork"), 1);
	}
	if (pid1 == 0)
		process1(data, av[2], env);
	waitpid(pid1, NULL, 0);
	process2(data, av[3], env);
	close_data(data);
	return (0);
}
