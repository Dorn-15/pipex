/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:09:14 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/22 17:34:27 by adoireau         ###   ########.fr       */
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

void	open_files(char *in, char *out, int (*fd)[2])
{
	(*fd)[0] = open(in, O_RDONLY);
	if ((*fd)[0] == -1)
	{
		perror(in);
		exit(EXIT_FAILURE);
	}
	(*fd)[1] = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*fd)[1] == -1)
	{
		close((*fd)[0]);
		perror(out);
		exit(EXIT_FAILURE);
	}
}

int	handle_first_process(int *fd, int *pipefd, char *cmd_str, char **env)
{
	pid_t	pid;
	char	**cmd;

	cmd = ft_split(cmd_str, ' ');
	if (!cmd)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		free_split(cmd);
		return (0);
	}
	if (pid == 0)
	{
		child_process1(fd, pipefd, cmd, env);
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
	free_split(cmd);
	return (pid);
}

void	handle_second_process(int *fd, int *pipefd, char *cmd_str, char **env)
{
	char	**cmd;

	cmd = ft_split(cmd_str, ' ');
	if (!cmd)
		return ;
	child_process2(fd, pipefd, cmd, env);
	free_split(cmd);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	int		pipefd[2];
	pid_t	pid;

	errno = 0;
	if (ac != 5)
		return (ac_error(ac));
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	open_files(av[1], av[4], &fd);
	pid = handle_first_process(fd, pipefd, av[2], env);
	if (pid == 0)
		return (perror("first process"), 1);
	handle_second_process(fd, pipefd, av[3], env);
	close_pipes(fd, pipefd, pid);
	return (0);
}
