/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/19 18:22:28 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

int main(int argc, char **argv)
{
	int	pipefd[2];
	char x;
	char y;
	
	// if (argc == 5)
	// 	ft_printf("1. %s\n2. %s\n3. %s\n4. %s", argv[1], argv[2], argv[3], argv[4]);
	// ft_printf("\n");
	if (pipe(pipefd) == -1)
		return (0);
	int pid = fork();
	if (pid == -1)
		return(0);	
	if (pid == 0)
	{
		close(pipefd[0]);
		x = argv[2][0];
		if (write(pipefd[1], &x, sizeof(char)) == -1)
			return(0);
		close(pipefd[1]);
		ft_printf("You entered: %c\n", x);
	}
	else
	{
		close(pipefd[1]);
		if (read(pipefd[0], &y, sizeof(char)) == -1)
			return(0);
		close(pipefd[0]);
		ft_printf("Got from child process %c\n", y);
		wait(NULL);
	}	
	return (0);
}