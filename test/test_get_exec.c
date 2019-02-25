/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 18:00:52 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/21 22:32:53 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

int		NullPathArgument(void)
{
	if (get_exec(NULL, NULL) == NULL_ARG)
		return (ISTRUE);
	else
		return (ISFALSE);
}

int		test_get_exec(void)
{
	t_stack tests;

	ft_stckinit(&tests);
	ft_printf("%@s: \n", "39", "GET EXEC");
	load_test(&tests,"Null path argument", NullPathArgument);
	return (run_test(&tests));
}
