/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_generate_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 20:40:50 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/21 21:15:16 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

static int		NullPathArgument(void)
{
	if (generate_exec(NULL, NULL) == NULL_ARG)
		return (ISTRUE);
	else
		return (ISFALSE);
}

static int		InvalidPath(void)
{
	t_prgm		glob;


	if (generate_exec(&glob, "::::") == FAILED_MALLOC)
		return (ISTRUE);
	return (ISFALSE);
}
int		test_generate_exec(void)
{
	t_stack tests;

	ft_stckinit(&tests);
	ft_printf("%@s: \n", "39", "GENERATE EXEC");
	load_test(&tests,"Invalid path argument", InvalidPath);
	load_test(&tests,"Null path argument", NullPathArgument);
	return (run_test(&tests));
}
