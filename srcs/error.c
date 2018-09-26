/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/05 18:39:21 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/09/26 16:12:48 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		err_usage(char *err)
{
	ft_putstr_fd("usage: ", 2);
	ft_putendl_fd(err, 2);
	return (1);
}

int		err_shell(char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(err, 2);
	return (1);
}

int		exec_error(int err, char *tmp, char *arg)
{
	if (err == 0)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(arg, 2);
	}
	if (err == -1)
	{
		ft_strdel(&tmp);
		return (-1);
	}
	if (err == -2)
	{
		ft_putstr_fd("minishell: permission denied: ", 2);
		ft_putendl_fd(arg, 2);
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
		ft_putstr_fd("cd: ", 2);
		if (access(path, 0))
			ft_putstr_fd("no such file or directory: ", 2);
		else
			ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(path, 2);
		return (-1);
	}
	stat(path, &path_stat);
	if (S_ISREG(path_stat.st_mode))
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putendl_fd(path, 2);
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
