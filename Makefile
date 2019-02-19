# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/26 23:18:40 by cempassi          #+#    #+#              #
#    Updated: 2019/02/19 01:00:32 by cempassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAMEDB = minishelldb
NAMET = Unit
LIB = $(LPATH)libft.a
LIBDB = $(LPATH)libftdb.a

CC = Clang
COMPILE = $(CC) -c
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

SRCS += main.c
SRCS += env.c
SRCS += builtin.c
SRCS += path.c

TEST += unit.c
TEST += tests.c
INCS += minishell.h
INCT += unit.h
DSYM = $(NAME).dSYM

OBJS = $(patsubst %.c, $(OPATH)%.o, $(SRCS))
OBJD = $(patsubst %.c, $(OPATH)db%.o, $(SRCS))
OBJT = $(patsubst %.c, $(OPATH)%.o, $(TEST))

vpath %.c srcs
vpath %.c test
vpath %.h includes

all : $(NAME)

run : $(NAME)
	./$<
	
test: $(UNIT)
	./$<

debug : $(NAMEDB)
	./$<

#Normal compilation

$(NAME): $(LIB) $(OPATH) $(OBJS) $(INCS)
	$(CC) -o $@ $(LIB) $(OBJS)
	
$(OBJS) : $(OPATH)%.o : %.c $(INCS)
	$(COMPILE) $(CFLAGS) $(IFLAGS) $< -o $@

#Unit testing
$(UNIT): $(LIB) $(OPATH) $(OBJS) $(OBJT)
	$(CC) -o $@ $(OBJS) $(LIB) $(OBJT)

$(OBJT) : $(OPATH)%.o : %.c $(INCT)
	$(COMPILE) $(CFLAGS) $(IFLAGS) $< -o $@

#Debug
$(NAMEDB): $(LIBDB) $(OPATH) $(OBJD) $(INCS)
	$(CC) $(DFLAGS) -o $@ $(LIBDB) $(OBJD)
	
$(OBJD) : $(OPATH)db%.o : %.c $(INCS)
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

re: fclean all

FORCE :

.PHONY: all clean fclean debug FORCE
