/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 15:34:47 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/02 21:29:10 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <limits.h>

/*
**  BUILTIN
*/
int		sh_cd(char *path, char ***env);
int		sh_pwd(char	**env);
int		sh_env(char	**env);
char	**sh_environ(char **environ);
int		sh_setenv(char *name, char *value, char ***env);

#endif
