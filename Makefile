# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/26 23:18:40 by cempassi          #+#    #+#              #
#    Updated: 2019/03/05 00:25:37 by cempassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAMEDB = minishelldb
NAMET = Unit
LIB = $(LPATH)libft.a
LIBDB = $(LPATH)libftdb.a

CC = Clang
COMPILE = $(CC) -c -g
DEBUG = $(CC) -g -c

MKDIR = mkdir -p
CLEANUP = rm -rf

WFLAGS += -Wall
WFLAGS += -Werror
WFLAGS += -Wextra
DFLAGS = -fsanitize=address
IFLAGS = -I $(IPATH) -I $(LIPATH)
CFLAGS = $(WFLAGS)

OPATH = obj/
SPATH = srcs/
IPATH = includes/
LPATH = libft/
LIPATH = libft/includes/

INCS += minishell.h
INCT += unit.h

SRCM += main.c

SRCS += basic_setup.c
SRCS += builtin.c
SRCS += env.c
SRCS += env_options.c
SRCS += error.c
SRCS += finders.c
SRCS += init.c
SRCS += get.c
SRCS += launcher.c
SRCS += process_line.c
SRCS += read_path.c
SRCS += setunsetenv.c
SRCS += split_input.c

TEST += unit.c
TEST += test_envinit.c
TEST += test_execinit.c
TEST += test_ft_getenv.c
TEST += test_get_path.c
TEST += test_generate_exec.c
TEST += test_line_processing.c
TEST += test_replace_variable.c
TEST += test_replace_home.c

DSYM = $(NAME).dSYM

OBJM = $(patsubst %.c, $(OPATH)%.o, $(SRCM))
OBJMD = $(patsubst %.c, $(OPATH)db%.o, $(SRCM))
OBJS = $(patsubst %.c, $(OPATH)%.o, $(SRCS))
OBJD = $(patsubst %.c, $(OPATH)db%.o, $(SRCS))
OBJT = $(patsubst %.c, $(OPATH)%.o, $(TEST))

vpath %.c srcs
vpath %.c test
vpath %.h includes

all : $(NAME)

run : $(NAME)
	./$<
	
test: $(NAMET)
	./$<

debug : $(NAMEDB)
	./$<

#Normal compilation

$(NAME): $(LIB) $(OPATH) $(OBJM) $(OBJS) $(INCS)
	$(CC) -o $@ $(LIB) $(OBJS) $(OBJM)
	
$(OBJS) : $(OPATH)%.o : %.c $(INCS)
	$(COMPILE) $(CFLAGS) $(IFLAGS) $< -o $@

$(OBJM) : $(OPATH)%.o : %.c $(INCS)
	$(COMPILE) $(CFLAGS) $(IFLAGS) $< -o $@

#Unit testing
$(NAMET): $(LIB) $(OPATH) $(OBJS) $(OBJT)
	$(CC)  -o $@ $(OBJS) $(LIB) $(OBJT)

$(OBJT) : $(OPATH)%.o : %.c $(INCT)
	$(DEBUG) $(CFLAGS) $(IFLAGS) $< -o $@

#Debug
$(NAMEDB): $(LIBDB) $(OPATH) $(OBJD) $(OBJMD) $(INCS)
	$(CC) $(DFLAGS) -o $@ $(LIBDB) $(OBJD) $(OBJMD)
	
$(OBJD) : $(OPATH)db%.o : %.c $(INCS)
	$(DEBUG) $(DFLAGS) $(CFLAGS) $(IFLAGS) $< -o $@

$(OBJMD) : $(OPATH)db%.o : %.c $(INCS)
	$(DEBUG) $(DFLAGS) $(CFLAGS) $(IFLAGS) $< -o $@

#Libraries
$(LIB) : FORCE
	$(MAKE) -C $(LPATH)

$(LIBDB) : FORCE
	$(MAKE) -C $(LPATH) debug

$(OPATH):
	$(MKDIR) $@

clean :
	$(MAKE) -C $(LPATH) clean
	$(CLEANUP) $(OBJS)
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(DSYM)

fclean : clean
	$(MAKE) -C $(LPATH) fclean
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(NAME)
	$(CLEANUP) $(NAMEDB)
	$(CLEANUP) $(NAMET)

re: fclean all

FORCE :

.PHONY: all clean fclean debug test FORCE
