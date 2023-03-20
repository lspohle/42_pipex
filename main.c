/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/20 12:51:07 by lspohle          ###   ########.fr       */
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

int main(int argc, char **argv)
{
	int	pipe_fd[2];
	int	file_fd[2];
	int pipe_id;
	char y;
	
	file_fd[0] = open(argv[1], O_RDONLY);
	file_fd[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file_fd[0] == -1 || file_fd[1] == -1)	
		return(close_files(file_fd, errno));
	if (argc != 5)
		return(0);
	if (pipe(pipe_fd) == -1)
		return (0);
	pipe_id = fork();
	if (pipe_id == -1)
		return(0);	
	else if (pipe_id == 0)
	{
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		if (ft_printf("%s", "HELLO WORLD") == -1)
			return(0);
	}
	else
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		ft_printf("Got from child process: ");
		while (read(0, &y, sizeof(char)) > 0)
			write(file_fd[1], &y, sizeof(char));
		wait(NULL);
	}
	return(close_files(file_fd, 0));
	ft_printf("%s", argv[argc]);
}