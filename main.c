/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 16:43:28 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/02 21:29:39 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int		sh_builtin(char **arg, char ***env)
{
	if (!arg[0])
		return (1);
	if (ft_strnstr(arg[0], "cd", 2) && arg[0][2] == '\0')
	{
		sh_cd(arg[1], env);
		return (1);
	}
	if (ft_strnstr(arg[0], "pwd", 3) && arg[0][3] == '\0')
	{
		sh_pwd(*env);
		return (1);
	}
	if (ft_strnstr(arg[0], "env", 3) && arg[0][3] == '\0')
	{
		sh_env(*env);
		return (1);
	}
	return (0);
}

void	sh_prompt(char **env)
{
	int		i;

	i = 0;
	if (env)
		;
	/*
	while (!ft_strnstr(env[i], "HOME=", 5))
		i++;
	home = env[i];
	i = 0;*/
	while (!ft_strnstr(env[i], "PWD=", 4))
		i++;
	ft_putstr("\e[1m@ \e[34;1m");
	ft_putstr(ft_strrchr(env[i], '/'));
	ft_putstr("\e[31;1m ▶ \e[0m");
}

void	sh_cmd(char ***env)
{
	char	*line;
	char	**arg;

	get_next_line(1, &line);
	arg = ft_strsplit(line, ' ');
	ft_strdel(&line);
	if (!sh_builtin(arg, env))
	{
		ft_putstr("miniSH: command not found: ");
		ft_putstr(arg[0]);
		ft_putstr("\n");
	}
	int i = 0;
	while (arg[i])
	{
		ft_strdel(&arg[i++]);
	}
	free(arg);
	// printf("%s\n", line);
}

char	**sh_environ(char **environ)
{
	char	**env;
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (environ[i])
		i++;
	if (!(env = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	printf("%i\n", i);
	i = 0;
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

int		main(int ac, char **av, char **environ)
{
	int		i;
	char	**env;

	env = sh_environ(environ);
	i = 0;
	if (av[ac])
		;
	while (1)
	{
		sh_prompt(env);
		sh_cmd(&env);
	}
	return (0);
}
