/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_line_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 04:18:51 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/01 19:51:06 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

int		NullStrArgument(void)
{
	t_prgm		glob;

	glob.line = NULL;
	if (split_input(&glob) == NULL_ARG)
		return (ISTRUE);
	return (ISFALSE);
}

int		OneSimpleArgument(void)
{
	t_prgm		glob;

	glob.line = "Salut";
	glob.error = 0;
	split_input(&glob);
	if (ft_strequ(glob.tab.av[0], "Salut") && glob.tab.ac == 1)
		return (ISTRUE);
	return (ISFALSE);
}

int		TwoSimpleArguments(void)
{
	t_prgm		glob;

	glob.line = "Salut Yo";
	glob.error = 0;
	split_input(&glob);
	if (ft_strequ(glob.tab.av[0], "Salut") && ft_strequ(glob.tab.av[1], "Yo"))
		return (ISTRUE);
	return (ISFALSE);
}

int		QuotedArguments(void)
{
	t_prgm		glob;

	glob.line = "\"Salut  Yo\"";
	glob.error = 0;
	split_input(&glob);
	if (ft_strequ(glob.tab.av[0], "Salut  Yo"))
		return (ISTRUE);
	return (ISFALSE);
}

int		NoEndQuoteArguments(void)
{
	t_prgm		glob;

	glob.line = "\"Salut  Yo";
	glob.error = 0;
	split_input(&glob);
	if (glob.error == UNCLOSED_COMMA)
		return (ISTRUE);
	return (ISFALSE);
}

int		EqualAndQuoteArguments(void)
{
	t_prgm		glob;

	glob.line = "setenv PATH=\"lavie\"";
	glob.error = 0;
	split_input(&glob);
	if (ft_strequ(glob.tab.av[0], "setenv")
		&& ft_strequ(glob.tab.av[1], "PATH")
		&& ft_strequ(glob.tab.av[2], "lavie"))
		return (ISTRUE);
	return (ISFALSE);
}

int		test_line_processing(void)
{
	t_stack tests;
	ft_printf("%@s: \n", BLUE, "LINE PROCESSING");
	load_test(&tests,"Equal And Quotes In Argument", EqualAndQuoteArguments);
	load_test(&tests,"No Endquote in line", NoEndQuoteArguments);
	load_test(&tests,"One quoted arguments", QuotedArguments);
	load_test(&tests,"Two Simple arguments", TwoSimpleArguments);
	load_test(&tests,"One Simple argument", OneSimpleArgument);
	load_test(&tests,"Return Null if Empty arg", NullStrArgument);
	return (run_test(&tests));
}
