/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplitq.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/03 19:27:56 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/09/18 21:01:46 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	check_quote(const char *s)
{
	int		i;
	int		j[2];

	i = 0;
	j[0] = 0;
	j[1] = 0;
	while (s[i])
	{
		if (s[i] == '"' && j[1] % 2)
			j[0]++;
		if (s[i] == '\'' && j[0] % 2)
			j[1]++;
		i++;
	}
	return (j[0] % 2 + j[1] % 2);
}

static void	split_count(char *tmp, int *i, int *y)
{
	if (tmp[(*i)] == '"')
	{
		(*y)++;
		(*i)++;
		while (tmp[(*i)++] != '"' && tmp[i[0]])
			;
	}
	else if (tmp[(*i)] == '\'')
	{
		(*y)++;
		(*i)++;
		while (tmp[(*i)++] != '\'' && tmp[i[0]])
			;
	}
	else if (ft_isprint(tmp[(*i)]) && tmp[(*i)] != ' ')
	{
		(*y)++;
		while (ft_isprint(tmp[(*i)]) && tmp[(*i)] != ' ' &&
		tmp[(*i)] != '"' && tmp[(*i)] != '\'')
			(*i)++;
	}
}

static char	*split_buf(char *tmp, int i[4])
{
	if (tmp[i[0]] == '"')
	{
		i[2] = ++i[0];
		while (tmp[i[0]] != '"' && tmp[i[0]])
			i[0]++;
	}
	else if (tmp[i[0]] == '\'')
	{
		i[2] = ++i[0];
		while (tmp[i[0]] != '\'' && tmp[i[0]])
			i[0]++;
	}
	else if (ft_isprint(tmp[i[0]]) && tmp[i[0]] != ' ')
	{
		i[2] = i[0];
		while (ft_isprint(tmp[i[0]]) && tmp[i[0]] != ' ' &&
		tmp[i[0]] != '"' && tmp[i[0]] != '\'')
			i[0]++;
	}
	if (tmp[i[0]] == '\'' || tmp[i[0]] == '"')
		return (ft_strndup(tmp + i[2], i[0]++ - i[2]));
	return (ft_strndup(tmp + i[2], i[0] - i[2]));
}

static char	**split_alloc(char *tmp)
{
	int		i;
	int		y;
	char	**out;

	i = 0;
	y = 0;
	while (tmp[i])
	{
		if (ft_isspace(tmp[i]))
			while (ft_isspace(tmp[i]))
				i++;
		else
			split_count(tmp, &i, &y);
	}
	y++;
	out = malloc(sizeof(char*) * y);
	out[y - 1] = NULL;
	return (out);
}

char		**ft_strsplitq(const char *s)
{
	int		i[4];
	char	*tmp;
	char	**out;

	ft_memset(i, 0, sizeof(i));
	if (s == NULL || check_quote(s))
		return (NULL);
	tmp = ft_strdup(s);
	out = split_alloc(tmp);
	while (tmp[i[0]])
	{
		if (ft_isspace(tmp[i[0]]))
			while (ft_isspace(tmp[i[0]]))
				i[0]++;
		else
			out[i[3]++] = split_buf(tmp, i);
	}
	ft_strdel(&tmp);
	return (out);
}
