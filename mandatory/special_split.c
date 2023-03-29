/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:26:15 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/29 17:29:23 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int ft_iterate_until_char(char *s, int i, char c, int *cnt)
{
	if (c == ' ')
		(*cnt)++;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static int	ft_cnt_sub_cmds(char *s)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 1;
	while (s[++i])
	{
		if (s[i] == ' ')
			i = ft_iterate_until_char(s, i, ' ', &cnt);
		if (s[i] == 34)
			i = ft_iterate_until_char(s, ++i, 34, &cnt);
		if (s[i] == 39)
			i = ft_iterate_until_char(s, ++i, 39, &cnt);
	}
	return (cnt);
}

static void	ft_cnt(char *s, size_t *start, size_t *len)
{
	while (s[(*start)] == ' ' && s[(*start)])
		(*start)++;
	(*len) = (*start);
	if (s[(*len)] == 34)
	{
		(*len)++;
		while (s[(*len)] != 34 && s[(*len)] != '\0')
			(*len)++;
		(*start)++;
	}
	else if (s[(*len)] == 39)
	{
		(*len)++;
		while (s[(*len)] != 39 && s[(*len)] != '\0')
			(*len)++;
		(*start)++;
	}
	else
	{
		while (s[(*len)] != ' ' && s[(*len)] != '\0')
			(*len)++;
	}
}

static char	**ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char	**mod_split(char *cmd)
{
	size_t	start;
	size_t	len;
	char	**substr;
	int		cnt_sub_cmds;
	
	if (cmd == NULL)
		return (NULL);
	substr = malloc (sizeof(char *) * (ft_cnt_sub_cmds(cmd) + 1));
	if (substr == NULL)
		return (NULL);
	cnt_sub_cmds = 0;
	start = 0;
	while (cnt_sub_cmds < ft_cnt_sub_cmds(cmd))
	{
		ft_cnt(cmd, &start, &len);
		substr[cnt_sub_cmds] = ft_substr(cmd, start, len - start);
		if (!substr[cnt_sub_cmds])
			return (ft_free(substr));
		cnt_sub_cmds++;
		start = len;
	}
	substr[cnt_sub_cmds] = NULL;
	return (substr);
}

char	**check_for_special(char *cmd)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (cmd[i])
	{
		if (cmd[i] == 34 || cmd[i] == 39)
			cnt++;
		i++;
	}
	if (cnt % 2 != 0)
		exit_cmd_failed("syntax error");
	return (mod_split(cmd));
}
