/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:39:29 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/22 21:02:51 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(t_data pipex, char *cmd)
{
	char	**cmd_split;
	char	*cmd_path;

	cmd_split = ft_split(cmd, ' ');
	if (cmd_split == NULL)
		display_error(1);
	cmd_path = get_cmd_path(&pipex, cmd_split[0]);
	if (cmd_path == NULL)
	{
		write(STDERR_FILENO, "pipex: ", 7);
		ft_putstr_fd(cmd_split[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	//	display_error(127);
	if (execve(cmd_path, cmd_split, pipex.envp) <= -1)
		display_error(1);
	free(cmd);
	free(cmd_path);
}

void	process_child(t_data pipex)
{
	dup2(pipex.file_fd[0], STDIN_FILENO);
	dup2(pipex.pipe_fd[1], STDOUT_FILENO);
	close(pipex.pipe_fd[1]);
	close(pipex.pipe_fd[0]);
	execute_command(pipex, pipex.argv[2]);
}

void	process_parent(t_data pipex)
{
	dup2(pipex.pipe_fd[0], STDIN_FILENO);
	dup2(pipex.file_fd[1], STDOUT_FILENO);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	execute_command(pipex, pipex.argv[pipex.argc - 2]);
}
