/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:09:14 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/17 10:49:00 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	int		fd[2];
	int		pipefd[2];
	char	**cmd1;
	char	**cmd2;
	pid_t	pid1;
	pid_t	pid2;

	if (ac < 5)
		return (ft_putstr_fd("error: too few arguments\n", 2), 1);
	else if (ac > 5)
		return (ft_putstr_fd("error: too many arguments\n", 2), 1);
	errno = 0;
	if (open_files(av[1], av[4], &fd) == 0)
		return (1);
	if (!split_cmds(av, &cmd1, &cmd2))
		return (print_err("split"), close_prog(&fd, cmd1, cmd2), 1);
	if (pipe(pipefd) == -1)
		return (print_err("pipe"), 1);
	pid1 = fork();
	if (pid1 == -1)
		return (print_err("fork"), 1);
	if (pid1 == 0)
		child_process1(fd, pipefd, cmd1, env);
	pid2 = fork();
	if (pid2 == -1)
		return (print_err("fork"), 1);
	if (pid2 == 0)
		child_process2(fd, pipefd, cmd2, env);
	close_pipes(fd, pipefd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_split(cmd1);
	free_split(cmd2);
	return (0);
}
