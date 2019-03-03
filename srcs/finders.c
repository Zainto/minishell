/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 04:23:54 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/03 00:46:51 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		var_filter(void *data, void *to_find)
{
	t_variable *variable;

	variable = data;	
	return (!ft_strequ(variable->name, (char *)to_find));
}

int		find_exec(void *data, void *to_find)
{
	t_status *exec;

	exec = data;
	if (ft_strequ(exec->path, (char *)to_find))
		return (1);
	return (ft_strequ(exec->name, (char *)to_find));
}

int			varcmp(void *data, void *to_find)
{
	t_variable	*variable;

	variable = data;
	return (ft_strequ(variable->name, (char *)to_find));
}

void	print_variable(t_list *node)
{
	t_variable	*variable;

	variable = (t_variable *)node->data;
	ft_printf ("%s=%s\n", variable->name, variable->data);
}

int		print_env(t_prgm *glob)
{
	ft_lstiter(glob->env, print_variable);	
	return (1);
}
