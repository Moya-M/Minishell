/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/07 15:37:30 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/15 13:51:40 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	TODO Gestion des return de execve
*/

int		sh_execute_path(char *path, char **arg, char **env)
{
	struct stat	path_stat;
	char		*tmp;
	char		*tmp2;
	pid_t		pid;
	int			st;

	tmp2 = ft_strjoin(path, "/");
	tmp = ft_strjoin(tmp2, arg[0]);
	ft_strdel(&tmp2);
	stat(tmp, &path_stat);
	if (access(tmp, 0) == -1 || S_ISREG(path_stat.st_mode) == 0)
	{
		ft_strdel(&tmp);
		return (-1);
	}
	pid = fork();
	if (pid == 0)
		execve(tmp, arg, env);
	if (pid != 0)
	{
		wait(&st);
		ft_strdel(&tmp);
		return (WEXITSTATUS(st));
	}
	ft_strdel(&tmp);
	return (-1);
}

int		sh_echo(char **arg, char **env)
{
	int i;

	i = 1;
	(void)env;
	while (arg[i])
	{
		ft_putstr(arg[i++]);
		ft_putstr(" ");
	}
	ft_putstr("\n");
	return (0);
}

int		sh_exit(int out, char **arg, char **env)
{
	int i;

	i = -1;
	if (arg[1] != NULL)
		out = ft_atoi(arg[1]);
	while (arg[++i])
		ft_strdel(&arg[i]);
	free(arg);
	i = -1;
	while (env[++i])
		ft_strdel(&env[i]);
	free(env);
	exit(out);
	return (out);
}
