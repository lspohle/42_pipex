/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_dbl_ptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:36:03 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/01 13:13:00 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_dbl_ptr(char **arr)
{
	int i = -1;
	while (arr[++i])
	{
		free(arr[i]);
		//arr[i] = NULL;
	}
	free(arr);
	//arr[i] = NULL;
	return (NULL);
}
