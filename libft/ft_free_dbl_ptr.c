/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_dbl_ptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:36:03 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/29 20:57:12 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_dbl_ptr(char **arr)
{
	while (*arr)
	{
		free(*arr);
		*arr = NULL;
		arr++;
	}
	free(*arr);
	*arr = NULL;
	return (NULL);
}
