/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 11:25:23 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/01 05:39:04 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_error(t_prgm *glob)
{
	glob->error_str[0] = "command not found";	
	glob->error_str[1] = "Null argument passed";	
	glob->error_str[2] = "System Failure on malloc";	
	glob->error_str[3] = "System Failure on Open";	
	glob->error_str[4] = "System Failure on Close";	
	glob->error_str[5] = "System Failure on Read";	
	glob->error_str[6] = "Unclosed comma";	
	glob->error_str[7] = "Cd takes only one argument";	
	glob->error_str[8] = "Not enough Argumends";	
	glob->error_str[9] = "Invalid path";	
	glob->error_str[10] = "Too many arguments";	
}

void	error_manager(t_prgm *glob)
{
	int		id;

	id = ft_abs(glob->error);
	if (id > 0 && id <= 4)
	{
		ft_dprintf(2, "minishell: %s\n", glob->error_str[id]);
		ms_exit(glob);
	}
	else if (id >= 5 && id <= 10)
		ft_dprintf(2, "minishell: %s\n", glob->error_str[id]);
	else 
		ft_dprintf(2, "minishell: %s: %s\n"
				, glob->error_str[id], glob->tab.av[0]);
	glob->error = 0;
}
