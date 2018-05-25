/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplittrim.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/24 18:20:54 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/05/25 16:56:01 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (s[i] == c || s[i] == ' ' || s[i] == '\t')
		i++;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			len++;
		i++;
	}
	return (len);
}

static void	ft_freetabs(char **tab, int k)
{
	while (k > 0)
	{
		k--;
		free(tab[k]);
	}
	free(tab);
}

static int	ft_countletters(char const *s, int i, char c)
{
	int j;

	j = 0;
	while (s[i] != ' ' && s[i] != '\t' && s[i] != c && s[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

static char	**ft_split(char const *s, char **tab, int i, char c)
{
	int j;
	int k;
	int cpt;

	j = 0;
	k = 0;
	cpt = 0;
	while (s[i] && k < ft_countwords(s, c))
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == c)
			i++;
		if (!(tab[k] = malloc(sizeof(char) * (ft_countletters(s, i, c) + 1))))
		{
			ft_freetabs(tab, k);
			return (NULL);
		}
		cpt = i + ft_countletters(s, i, c);
		while (i < cpt)
			tab[k][j++] = s[i++];
		tab[k][j] = '\0';
		j = 0;
		k++;
	}
	tab[k] = 0;
	return (tab);
}

char		**ft_strsplittrim(char const *s, char c)
{
	int		i;
	char	**tab;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(tab = malloc(sizeof(char*) * (ft_countwords(s, c) + 1))))
		return (NULL);
	return (ft_split(s, tab, i, c));
}
