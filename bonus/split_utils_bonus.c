/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:26:23 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/28 09:26:25 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_quotes(int *i, char *str)
{
	int	count;

	count = 0;
	if (str[(*i)] == 34)
	{
		(*i)++;
		while (str[(*i)] != 34 && str[(*i)])
			(*i)++;
		if (str[(*i) + 1] != '\0')
			count++;
	}
	if (str[(*i)] == 39)
	{
		(*i)++;
		while (str[(*i)] != 39 && str[(*i)])
			(*i)++;
		if (str[(*i) + 1] != '\0')
			count++;
	}
	return (count);
}
