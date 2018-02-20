/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/07 15:37:30 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/20 13:11:41 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		sh_execute_path(char *path, char **arg, char **env)
{
	struct stat	path_stat;
	char		*tmp;
	char		*tmp2;
	pid_t		pid;
	int			st;

	!(tmp2 = ft_strjoin(path, "/")) ? sh_exit(-1, arg, env) : 0;
	!(tmp = ft_strjoin(tmp2, arg[0])) ? sh_exit(-1, arg, env) : 0;
	ft_strdel(&tmp2);
	stat(tmp, &path_stat);
	if (access(tmp, 0) == -1 || S_ISREG(path_stat.st_mode) == 0)
	{
		ft_strdel(&tmp);
		return (-1);
	}
	pid = fork();
	(pid == 0) ? execve(tmp, arg, env) : 0;
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
	int	j;

	i = 1;
	(void)env;
	while (arg[i])
	{
		j = 0;
		if (arg[i][0] == '"' || arg[i][0] == '\'' || arg[i][0] == '`')
			j++;
		ft_putstr(arg[i++] + j);
		if (j)
			ft_putstr("\b ");
		else
			ft_putstr(" ");
	}
	ft_putstr("\n");
	return (0);
}

int		err_usage(char *err)
{
	ft_putstr("usage: ");
	ft_putendl(err);
	return (1);
}

int		sh_exit(int out, char **arg, char **env)
{
	int i;

	i = -1;
	if (env != NULL)
	{
		while (env[++i])
			ft_strdel(&env[i]);
		if (arg != NULL)
			if (arg[1] != NULL)
				out = ft_atoi(arg[1]);
	}
	i = -1;
	if (arg != NULL)
		while (arg[++i] != NULL)
			ft_strdel(&arg[i]);
	free(arg);
	i = -1;
	free(env);
	exit(out);
	return (out);
}
