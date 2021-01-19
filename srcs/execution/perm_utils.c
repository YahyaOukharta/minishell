/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:00:17 by youkhart          #+#    #+#             */
/*   Updated: 2021/01/19 09:00:20 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_regular_file(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int		is_link_file(const char *path)
{
	struct stat path_stat;

	return (!lstat(path, &path_stat));
}

int		is_exe_usr(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return ((S_IXUSR) & path_stat.st_mode);
}

int		is_exe_grp(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return ((S_IXGRP) & path_stat.st_mode);
}

int		is_exe_oth(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return ((S_IXOTH) & path_stat.st_mode);
}
