/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/30 17:42:21 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2017/12/08 18:16:49 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_countc(char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

static void		ft_stros(char **str, int i)
{
	char *tmp;

	tmp = *str;
	if (!(*str = ft_strdup(*str + i + 1)))
		return ;
	ft_strdel(&tmp);
}

static int		file_reader(int fd, char **str)
{
	int		len;
	char	*tmp;
	char	buf[BUFF_SIZE + 1];

	len = 0;
	while ((len = read(fd, &buf, BUFF_SIZE)) > 0)
	{
		buf[len] = '\0';
		if (!(tmp = ft_strjoin(*str, buf)))
			return (-1);
		if (*str[0] != '\0')
			ft_strdel(str);
		if (!(*str = ft_strdup(tmp)))
			return (-1);
		ft_strdel(&tmp);
		if (ft_strchr(*str, '\n') != NULL)
			break ;
	}
	if (len == -1)
		return (-1);
	return (0);
}

static int		handle_return(char **str, char **line)
{
	size_t		i;

	if (*str)
	{
		i = ft_countc(*str, '\n');
		if (*str[0] != '\0')
			if (!(*line = ft_strndup(*str, i)))
				return (-1);
		if (*line == NULL)
		{
			ft_strdel(str);
			return (0);
		}
		if (*str[0] != '\0' && i != 0)
			i == ft_strlen(*str) ? ft_strdel(str) : ft_stros(str, i);
	}
	else
		free(*str);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	int			len;
	char		*tmp;
	static char	*str = "";

	if (fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	if (str == NULL)
		if (!(str = ft_strdup("")))
			return (-1);
	if ((len = 0) == 0 && file_reader(fd, &str) == -1)
		return (-1);
	if (str[0] == '\n')
	{
		tmp = str;
		if (!(str = ft_strdup(str + 1)))
			return (-1);
		free(tmp);
		if (str[0] == '\0')
			ft_strdel(&str);
		ft_strdel(line);
		return ((!(*line = ft_strdup(""))) ? -1 : 1);
	}
	return (handle_return(&str, line));
}
