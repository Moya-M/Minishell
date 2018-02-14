/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/07 15:37:30 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/14 20:27:16 by mmoya       ###    #+. /#+    ###.fr     */
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

	tmp2 = ft_strjoin(path, "/");
	tmp = ft_strjoin(tmp2, arg[0]);
	ft_strdel(&tmp2);
	stat(tmp, &path_stat);
	if (access(tmp, 0) == -1 || S_ISREG(path_stat.st_mode) == 0)
	{
		ft_strdel(&tmp);
		return (0);
	}
	pid = fork();
	if (pid == 0)
		execve(tmp, arg, env);
	if (pid != 0)
	{
		wait(NULL);
		ft_strdel(&tmp);
		return (1);
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
	return (1);
}
