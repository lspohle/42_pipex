/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:48:24 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/28 21:48:26 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_env_path(char **envp)
{
	if (*envp == NULL)
		return ("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/ \
				local/munki:/opt/X11/bin:/Library/Apple/usr/bin");
	while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	return (*envp + 5);
}

static char	*get_cmd_path(t_data *pipex, char *cmd)
{
	char	*cmd_path;

	pipex->env_paths = ft_split(get_env_path(pipex->envp), ':');
	if (pipex->env_paths == NULL)
		free (pipex->env_paths);
	while (*pipex->env_paths != NULL)
	{
		*pipex->env_paths = ft_strjoin(*pipex->env_paths, "/");
		cmd_path = ft_strjoin(*pipex->env_paths, cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		pipex->env_paths++;
		free (cmd_path);
	}
	while (*pipex->env_paths != NULL)
		free (*pipex->env_paths);
	free (*pipex->env_paths);
	return (NULL);
}

static void	execute_command(t_data *pipex, char *cmd)
{
	char	**cmd_split;
	char	*cmd_path;

	cmd_split = check_for_special(cmd);
	if (cmd_split == NULL)
		exit_cmd_failed("split");
	cmd_path = get_cmd_path(pipex, cmd_split[0]);
	if (cmd_path == NULL)
		exit_cmd_not_found(cmd_split[0]);
	if (execve(cmd_path, cmd_split, pipex->envp) <= -1)
		exit_cmd_failed("execve");
	free(cmd_split);
	free(cmd_path);
}

void	process_parent(t_data *pipex)
{
	waitpid(pipex->pid, NULL, WNOHANG);
	close(pipex->pipe_fd[1]);
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	close(pipex->pipe_fd[0]);
}

void	process_child(t_data *pipex, char *cmd)
{
	close(pipex->pipe_fd[0]);
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->pipe_fd[1]);
	if (ft_strncmp(cmd, pipex->argv[pipex->argc - 2], sizeof(cmd)) == 0)
	{
		close(pipex->pipe_fd[1]);
		dup2(pipex->pipe_fd[0], STDIN_FILENO);
		close(pipex->pipe_fd[0]);
		dup2(pipex->file_fd[1], STDOUT_FILENO);
		close(pipex->file_fd[1]);
	}
	execute_command(pipex, cmd);
}
