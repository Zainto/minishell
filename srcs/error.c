/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 11:25:23 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/04 21:35:06 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_error(t_prgm *glob)
{
	glob->errstr[0] = "minishell";
	glob->errstr[1] = "command not found";
	glob->errstr[2] = "System Failure on malloc";
	glob->errstr[3] = "System Failure on Open";
	glob->errstr[4] = "System Failure on Close";
	glob->errstr[5] = "System Failure on Read";
	glob->errstr[6] = "Unclosed comma";
	glob->errstr[7] = "Cd takes only one argument";
	glob->errstr[8] = "Not enough Argumends";
	glob->errstr[9] = "Invalid path";
	glob->errstr[10] = "Too many arguments";
	glob->errstr[11] = "Is not a directory";
	glob->errstr[12] = "Wrong number of Arguments";
	glob->errstr[13] = "No arguments to unset";
	glob->errstr[14] = "Null argument passed";
}

void	error_manager(t_prgm *glob)
{
	const char	**errstr;
	int			errno;
	int			id;

	errno = ft_abs(glob->error);
	glob->error = 0;
	id = glob->tab.id;
	errstr = glob->errstr;
	if (errno == 1)
		ft_dprintf(2, "%s: %s: %s\n", *errstr, errstr[errno], glob->tab.av[id]);
	else if (errno >= 2 && errno <= 5)
	{
		ft_dprintf(2, "%s: %s\n", *errstr, errstr[errno]);
		ms_exit(glob);
	}
	else if (errno >= 6 && errno <= 14)
		ft_dprintf(2, "%s: %s\n", *errstr, errstr[errno]);
	return ;
}
