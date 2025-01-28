/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:18:51 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/28 13:43:09 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/include/libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		fd[2];
	int		pipefd[2];
	char	**cmd;
	char	*cmd_path;
}	t_pipex;

void	close_data(t_pipex *data);

char	*find_path(char *cmd, char **env);
void	execute_cmd(t_pipex *data, char **env);

void	process1(t_pipex *data, char *cmd_str, char **env);
void	process2(t_pipex *data, char *cmd_str, char **env);

#endif
