/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/05 18:39:21 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 17:19:36 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		err_usage(char *err)
{
	ft_putstr("usage: ");
	ft_putendl(err);
	return (1);
}

int		err_shell(char *err)
{
	ft_putstr("minishell: ");
	ft_putendl(err);
	return (1);
}

int		exec_error(int err, char *tmp, char *arg)
{
	if (err == 0)
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(arg);
	}
	if (err == -1)
	{
		ft_strdel(&tmp);
		return (-1);
	}
	if (err == -2)
	{
		ft_putstr("minishell: permission denied: ");
		ft_putendl(arg);
		ft_strdel(&tmp);
		return (-2);
	}
	return (-1);
}

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

char	*cd_checkenv(char **arg, char ***env, int *b)
{
	char	*new;

	*b = 0;
	new = arg[1];
	if (new == NULL)
		if ((new = sh_getenv("HOME", *env)) == 0)
			new = ".";
	if (ft_strcmp(new, "-") == 0)
	{
		*b = 1;
		ft_strdel(&new);
		if ((new = ft_strdup(sh_getenv("OLDPWD", *env))) == 0)
		{
			new = ft_strdup(".");
			arg[1] = new;
		}
		arg[1] = new;
	}
	return (new);
}
