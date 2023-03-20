/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/20 17:23:18 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	close_files(int file_fd[2], int errnum)
{
	if (errnum > 0)
		ft_printf(RED"Error: "ESC"%s\n", strerror(errno));
	close(file_fd[0]);
	close(file_fd[1]);
	return(0);
}

int	display_error(int errnum)
{
	ft_printf(RED"Error: "ESC"%s\n", strerror(errnum));
	return(0);
}

int main(int argc, char **argv)
{
	int	pipe_fd[2];
	int	file_fd[2];
	int pipe_id;
	char path[] = "/bin/ls";
	char *str[] = {"ls", "-l", NULL};
	char *envp[] = {"/usr/bin/env", NULL};
	char path1[] = "/usr/bin/wc";
	char *str1[] = {"wc", "-c", NULL};
	char *envp1[] = {"/usr/bin/env", NULL};
	
	if (argc != 5)
		return(display_error(EINVAL));
	file_fd[0] = open(argv[1], O_RDONLY);
	if (file_fd[0] == -1)
		return(display_error(errno));
	file_fd[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file_fd[1] == -1)	
		return(display_error(errno));
	if (pipe(pipe_fd) == -1)
		return(display_error(errno));
	pipe_id = fork();
	if (pipe_id == -1)
		return(display_error(errno));
	else if (pipe_id == 0)
	{
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		execve(path, str, envp);
		// if (ft_printf("%s", "HELLO WORLD") == -1)
		// 	return(0);
	}
	else
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		ft_printf("Got from child process: ");
		// while (read(0, &y, sizeof(char)) > 0)
		// 	write(file_fd[1], &y, sizeof(char));
		execve(path1, str1, envp1);
		wait(NULL);
	}
	return(close_files(file_fd, 0));
	ft_printf("%s", argv[argc]);
}


