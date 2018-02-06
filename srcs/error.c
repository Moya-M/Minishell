/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/05 18:39:21 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/05 19:13:32 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

int		cd_error(char *path)
{
	struct stat path_stat;

	if (access(path, R_OK))
	{
		ft_putstr("cd: ");
		if (access(path, 0))
			ft_putstr("no such file or directory: ");
		else
			ft_putstr("permission denied: ");
		ft_putendl(path);
		return (-1);
	}
	stat(path, &path_stat);
	if (S_ISREG(path_stat.st_mode))
	{
		ft_putstr("cd: not a directory: ");
		ft_putendl(path);
		return (-1);
	}
	return (1);
}
