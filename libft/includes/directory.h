/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 06:52:58 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/18 07:38:54 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTORY_H
# define DIRECTORY_H
# include <sys/stat.h>
# include "libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <uuid/uuid.h>

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct			s_status
{
	t_stat				info;
	char				*path;
	char				*name;
}						t_status;

int						ft_dirlist(t_list **dirlist, char *path);
void					ft_dirdel(t_list **dirlist);
#endif