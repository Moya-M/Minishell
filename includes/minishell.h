/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 15:34:47 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/06 15:09:28 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <sys/stat.h>
# include <stdio.h>
# include <limits.h>

/*
**  BUILTIN
*/
int		sh_cd(char *path, char ***env);
int		cd_error(char *path);
int		sh_pwd(char	**env);
int		sh_env(char	**env);
char	**sh_environ(char **environ);
char	*sh_getenv(char *key, char **env);
int		sh_setenv(char *name, char *value, char ***env);
int		sh_getenv_id(char *key, char **env);
int		sh_execute(char **arg, char **env);

#endif
