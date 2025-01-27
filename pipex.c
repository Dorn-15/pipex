/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:09:14 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/27 12:01:39 by adoireau         ###   ########.fr       */
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

void	open_files(char *in, char *out, int fd[2])
{
	fd[0] = open(in, O_RDONLY);
	if (fd[0] == -1)
	{
		perror(in);
	}
	fd[1] = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] == -1)
	{
		close(fd[0]);
		perror(out);
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	int		pipefd[2];
	pid_t	pid1;

	errno = 0;
	if (ac != 5)
		return (ac_error(ac));
	open_files(av[1], av[4], fd);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid1 = fork();
	if (pid1 == -1)
		return (perror("fork"), 1);
	if (pid1 == 0)
		process1(fd, pipefd, av[2], env);
	else
		process2(fd, pipefd, av[3], env);
	return (0);
}
