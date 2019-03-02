/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 11:25:23 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/02 19:57:55 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_error(t_prgm *glob)
{
	glob->e_str[0] = "minishell";
	glob->e_str[1] = "command not found";
	glob->e_str[2] = "System Failure on malloc";
	glob->e_str[3] = "System Failure on Open";
	glob->e_str[4] = "System Failure on Close";
	glob->e_str[5] = "System Failure on Read";
	glob->e_str[6] = "Unclosed comma";
	glob->e_str[7] = "Cd takes only one argument";
	glob->e_str[8] = "Not enough Argumends";
	glob->e_str[9] = "Invalid path";
	glob->e_str[10] = "Too many arguments";
	glob->e_str[11] = "Is not a directory";
	glob->e_str[12] = "Wrong number of Arguments";
	glob->e_str[13] = "No arguments to unset";
	glob->e_str[14] = "Null argument passed";
}

void	error_manager(t_prgm *glob)
{
	const char	**e_str;
	int			errno;
	int			id;

	errno = ft_abs(glob->error);
	glob->error = 0;
	id = glob->tab.id;
	e_str = glob->e_str;
	if (errno == 1)
		ft_dprintf(2, "%s: %s: %s\n", e_str, e_str[errno], glob->tab.av[id]);
	else if (errno >= 2 && errno <= 5)
	{
		ft_dprintf(2, "%s: %s\n", e_str, e_str[errno]);
		ms_exit(glob);
	}
	else if (errno >= 6 && errno <= 14)
		ft_dprintf(2, "%s: %s\n", e_str, e_str[errno]);
	return ;
}
