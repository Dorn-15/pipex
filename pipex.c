/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:09:14 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/21 16:07:28 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ac_error(int ac)
{
	if (ac < 5)
		ft_putstr_fd("error: too few arguments\n", 2);
	else
		ft_putstr_fd("error: too many arguments\n", 2);
	return (1);
}

void	open_files(char *in, char *out, int (*fd)[2])
{
	(*fd)[0] = open(in, O_RDONLY);
	if ((*fd)[0] == -1)
	{
		perror(in);
		exit(errno);
	}
	(*fd)[1] = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*fd)[1] == -1)
	{
		close((*fd)[0]);
		perror(out);
		exit(errno);
	}
}

int	split_cmds(char **av, char ***cmd1, char ***cmd2)
{
	*cmd1 = ft_split(av[2], ' ');
	*cmd2 = ft_split(av[3], ' ');
	if (!*cmd1 || !*cmd2)
		return (0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	int	fd[2];
	int	pipefd[2];
	char	**cmd[2];
	pid_t	pid[2];

	if (ac != 5)
		return (ac_error(ac));
	open_files(av[1], av[ac - 1], &fd);
	if (!split_cmds(av, &cmd[0], &cmd[1]))
		return (perror("split"), close_prog(&fd, cmd[0], cmd[1]), 1);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid[0] = fork();
	if (pid[0] == -1)
		return (perror("fork"), 1);
	if (pid[0] == 0)
		child_process1(fd, pipefd, cmd[0], env);
	pid[1] = fork();
	if (pid[1] == -1)
		return (perror("fork"), 1);
	if (pid[1] == 0)
		child_process2(fd, pipefd, cmd[1], env);
	close_pipes(fd, pipefd, pid);
	free_split(cmd[0]);
	free_split(cmd[1]);
	return (0);
}
