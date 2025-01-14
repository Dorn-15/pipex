/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:09:14 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/13 16:55:13 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_err(char *err)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\n", 2);
}

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
	free_split(cmd1);
	free_split(cmd2);
	close((*fd)[0]);
	close((*fd)[1]);
}

int	main(int ac, char **av)
{
	int		fd[2];
	int		pipefd[2];
	char	**cmd1;
	char	**cmd2;

	if (ac < 5)
		return (ft_putstr_fd("error: too few arguments\n", 2), 1);
	else if (ac > 5)
		return (ft_putstr_fd("error: too many arguments\n", 2), 1);
	errno = 0;
	if (open_files(av[1], av[4], &fd) == 0)
		return (1);
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	close_prog(&fd, cmd1, cmd2);
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}
