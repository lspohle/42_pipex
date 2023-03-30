/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:06:55 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/22 13:45:33 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Note
//     Prototyped as char **ft_split(char const *s, char c)
//     -> allocates (with malloc(3)) returns an array of strings obtained by
//        splitting ’s’ using the character ’c’ as a delimiter
//     -> the array must end with a NULL pointer
//     -> return: array of new strings resulting from the split
//                NULL if allocation fails
//     -> external functions: malloc(3), free

#include "libft.h"

static int	get_substring(const char *s, char c, char **substr, int i)
{
	char			*tmp;
	unsigned int	start;
	int				specials;

	start = i;
	specials = 0;
	while (specials % 2 == 1 || (s[i] != c && s[i] != '\0'))
	{
		if (s[i] == 39 || s[i] == 34)
			specials++;
		i++;
	}
	*substr = ft_substr(s, start, i - start);
	if (specials > 0)
	{
		tmp = ft_strtrim(*substr);
		free(*substr);
		*substr = tmp;
	}
	return (++i);
}

static int	ft_count_strings(const char *s, char c)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			counter++;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (s[i] == '\0')
				break ;
		}
	}
	return (counter);
}

static char	**ft_split_string(char **result, const char *s, char c)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		i = get_substring(s, c, &result[j], i);
		if (!result[j++])
		{
			free(result);
			return (NULL);
		}
		if (s[i - 1] == '\0')
			break ;
	}
	result[j] = NULL;
	return (result);
}

// Allocates and returns an array of strings obtained by splitting ’s’ using 
// the character ’c’ as a delimiter
// The array must end with a NULL pointer
// Returns array of new strings resulting from the split
// Returns NULL if allocation fails
char	**ft_split(const char *s, char c)
{
	char	**result;

	result = (char **)malloc ((ft_count_strings(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (ft_split_string(result, s, c) == NULL)
		return (NULL);
	return (result);
}
