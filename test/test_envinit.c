/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_envinit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:51:07 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/21 21:01:35 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

static int			NullArgWithEmptyEnv(void)
{
	t_prgm	glob;

	if (envinit(&glob, NULL) == NULL_ARG)
		return (ISTRUE);
	else
		return (ISFALSE);
}

static int			EnvIsNullTerminated(void)
{
	t_prgm	glob;
	char	*env[2];

	env[0] = NULL;
	if(envinit(&glob, env) == 0)
		return (ISTRUE);
	else
		return (ISFALSE);
}

static int			GetOneValidName(void)
{
	t_prgm	glob;
	char	*env[2];

	env[0] = "Tata=Toto";
	env[1] = NULL;
	glob.env = NULL;
	envinit(&glob, env);
	if(ft_strequ(((t_variable *)glob.env->data)->name, "Tata"))
		return (ISTRUE);
	else
		return (ISFALSE);
}

static int			GetOneValidData(void)
{
	t_prgm	glob;
	char	*env[2];

	env[0] = "Tata=Toto";
	env[1] = NULL;
	glob.env = NULL;
	envinit(&glob, env);
	if(ft_strequ(((t_variable *)glob.env->data)->data, "Toto"))
		return (ISTRUE);
	else
		return (ISFALSE);
}

static int			GetThirtyValidName(void)
{
	t_prgm	glob;
	t_variable	*variable;
	char	*env[32];
	int		i;

	i = 30;
	env[0] = "TERM_SESSION_ID=w0t1p1:A4F51F3E-6405-4DE2-9D98-5272DF94A19E";
	env[1] = "SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.2WzclLtWJZ/Listeners";
	env[2] = "Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.wX48Jlm54h/Render";
	env[3] = "COLORFGBG=15;0";
	env[4] = "ITERM_PROFILE=Default";
	env[5] = "XPC_FLAGS=0x0";
	env[6] = "LANG=en_US.UTF-8";
	env[7] = "PWD=/Users/cempassi/Programming/42/minishell";
	env[8] = "SHELL=/bin/zsh";
	env[9] = "TERM_PROGRAM_VERSION=3.2.3";
	env[10] = "TERM_PROGRAM=iTerm.app";
	env[11] = "PATH=/Users/cempassi/.brew/bin:/Users/cempassi/Applications/bin:/usr/local/share:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/Library/Frameworks/Mono.framework/Versions/Current/Commands:/usr/local/munki";
	env[12] = "COLORTERM=truecolor";
	env[13] = "TERM=xterm-256color";
	env[14] = "HOME=/Users/cempassi";
	env[15] = "TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n0003ygh000zlw/T/";
	env[16] = "USER=cempassi";
	env[17] = "XPC_SERVICE_NAME=0";
	env[18] = "LOGNAME=cempassi";
	env[19] = "__CF_USER_TEXT_ENCODING=0x7E7C:0:0";
	env[20] = "ITERM_SESSION_ID=w0t1p1:A4F51F3E-6405-4DE2-9D98-5272DF94A19E";
	env[21] = "SHLVL=1";
	env[22] = "OLDPWD=/Users/cempassi/Programming/42/minishell";
	env[23] = "ZSH=/Users/cempassi/.oh-my-zsh";
	env[24] = "PAGER=less";
	env[25] = "LESS=-R";
	env[26] = "LC_CTYPE=en_US.UTF-8";
	env[27] = "LSCOLORS=Gxfxcxdxbxegedabagacad";
	env[28] = "MANPATH=~/Applications/valgrind/share/man/man1:~/Applications/vim/share/man/:";
	env[29] = "MAIL=cempassi@student.42.fr";
	env[30] = "_=/usr/bin/env";
	env[31] = NULL;
	glob.env = NULL;
	envinit(&glob, env);
	while(i >= 0)
	{
		variable = (t_variable *)glob.env->data;
		if(!ft_strnequ(variable->name, env[i], ft_strcspn(env[i], "=")))
			return (ISFALSE);
		glob.env = glob.env->next;
		i--;
	}
	return (ISTRUE);
}

static int			GetThirtyValidData(void)
{
	t_prgm	glob;
	t_variable	*variable;
	char	*env[32];
	int		i;

	i = 30;
	env[0] = "TERM_SESSION_ID=w0t1p1:A4F51F3E-6405-4DE2-9D98-5272DF94A19E";
	env[1] = "SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.2WzclLtWJZ/Listeners";
	env[2] = "Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.wX48Jlm54h/Render";
	env[3] = "COLORFGBG=15;0";
	env[4] = "ITERM_PROFILE=Default";
	env[5] = "XPC_FLAGS=0x0";
	env[6] = "LANG=en_US.UTF-8";
	env[7] = "PWD=/Users/cempassi/Programming/42/minishell";
	env[8] = "SHELL=/bin/zsh";
	env[9] = "TERM_PROGRAM_VERSION=3.2.3";
	env[10] = "TERM_PROGRAM=iTerm.app";
	env[11] = "PATH=/Users/cempassi/.brew/bin:/Users/cempassi/Applications/bin:/usr/local/share:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/Library/Frameworks/Mono.framework/Versions/Current/Commands:/usr/local/munki";
	env[12] = "COLORTERM=truecolor";
	env[13] = "TERM=xterm-256color";
	env[14] = "HOME=/Users/cempassi";
	env[15] = "TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n0003ygh000zlw/T/";
	env[16] = "USER=cempassi";
	env[17] = "XPC_SERVICE_NAME=0";
	env[18] = "LOGNAME=cempassi";
	env[19] = "__CF_USER_TEXT_ENCODING=0x7E7C:0:0";
	env[20] = "ITERM_SESSION_ID=w0t1p1:A4F51F3E-6405-4DE2-9D98-5272DF94A19E";
	env[21] = "SHLVL=1";
	env[22] = "OLDPWD=/Users/cempassi/Programming/42/minishell";
	env[23] = "ZSH=/Users/cempassi/.oh-my-zsh";
	env[24] = "PAGER=less";
	env[25] = "LESS=-R";
	env[26] = "LC_CTYPE=en_US.UTF-8";
	env[27] = "LSCOLORS=Gxfxcxdxbxegedabagacad";
	env[28] = "MANPATH=~/Applications/valgrind/share/man/man1:~/Applications/vim/share/man/:";
	env[29] = "MAIL=cempassi@student.42.fr";
	env[30] = "_=/usr/bin/env";
	env[31] = NULL;
	glob.env = NULL;
	envinit(&glob, env);
	while(i >= 0)
	{
		variable = (t_variable *)glob.env->data;
		if(!ft_strequ(variable->data, env[i] + ft_strcspn(env[i], "=") + 1))
			return (ISFALSE);
		glob.env = glob.env->next;
		i--;
	}
	return (ISTRUE);
}

int			test_envinit(void)
{
	t_stack	tests;

	ft_stckinit(&tests);
	ft_printf("%@s: \n", "39", "ENVINIT");
	load_test(&tests, "Thirty Valid Data", GetThirtyValidData);
	load_test(&tests, "Thirty Valid Name", GetThirtyValidName);
	load_test(&tests, "One Valid Data", GetOneValidData);
	load_test(&tests, "One Valid Name", GetOneValidName);
	load_test(&tests, "Env is null terminated", EnvIsNullTerminated);
	load_test(&tests, "NULL env as argument", NullArgWithEmptyEnv);
	return (run_test(&tests));
}
