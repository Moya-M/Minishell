/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 15:34:18 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 18:11:03 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"
/*
int		sh_setenv(char *nv, char **env)
{
	int i;

	i = 0;
	while (!ft_strnstr(env[i], name, ft_strlen(name)))
		i++;
	env[i] = ft_strdup(ft_st);
	return (1);
}*/

int		sh_cd(char *path, char **env)
{
	char	*cur;

	cur = ft_strnew(PATH_MAX);
	chdir(path);
	cur = getcwd(cur, PATH_MAX);
//	ft_setenv("PATH=", cur, env);
	return (1);
}

int		sh_pwd(char **env)
{
	char	*cur;

	ft_strnew(PATH_MAX + 1);
	cur = getcwd(cur, PATH_MAX);/*
	if (ft_strstr(env[i], home))
		ft_putstr("~");
	else
		ft_putstr(ft_strrchr(env[i], '/') + 1);*/
	ft_putstr(ft_strcat(cur, "\n"));
	return (1);
}
