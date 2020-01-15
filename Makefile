# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/28 01:21:35 by roliveir          #+#    #+#              #
#    Updated: 2019/09/22 11:51:47 by roliveir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include mk/srcs.mk

CC = gcc
LIBS = -lm #-lft -fsanitize=address
LIBSFOLDERS = -L./libft
vpath %.c $(dir MAKEFILE_LIST)
CFLAGS = -Wall -Wextra -Werror -I./includes -I./libft/includes
GLFLAGS = -lglut -lGL -lGLEW -lGLU
OBJDIR = .o
UNAME = $(shell uname)

NAME = decipher

OBJS = $(subst .c,.o,$(subst ./srcs/,./$(OBJDIR)/,$(SRCS)))
DEPS = $(subst .c,.d,$(subst ./srcs/,./$(OBJDIR)/,$(SRCS)))

all: $(NAME)

$(NAME): $(OBJS) | lib_rule
	@$(RM) tmp_log
	@$(RM) tmp_errors
	@if  [ -e files_missing ]; then \
		printf "\033[1;31m\n[$(NAME) compilation failed]\033[0m\n"; \
	else \
		$(CC) $(OBJS) -o $(NAME) $(LIBSFOLDERS) $(LIBS) $(GLFLAGS); \
		printf "\033[1;36m\n[$(NAME) compilation successful]\033[0m\n"; \
	fi;
	@$(RM) files_missing

$(OBJDIR):
	@$(shell mkdir -p $(OBJDIR))

$(OBJDIR)/%.o: srcs/%.c | $(OBJDIR)
	@$(shell mkdir -p $(dir $@))
	@printf "%-50s" "Precompiling $(notdir $@)..."
	@$(CC) $(CFLAGS) -c -o $@ $< 2> ./tmp_log || /usr/bin/touch ./tmp_errors
	@if [ -e tmp_errors ]; then \
		printf "\033[1;31m[KO]\n\033[0m" && /bin/cat 1>&2 ./tmp_log && touch files_missing; \
	elif test -s ./tmp_log; then \
		printf "\033[1;33m[WARNING]\n\033[0m" && /bin/cat ./tmp_log; \
	else \
		printf "\033[1;32m[OK]\n\033[0m"; \
	fi;
	@$(RM) ./tmp_errors

clean:
	@$(MAKE) -C libft clean --no-print-directory
	@$(MAKE) -C minilibx clean --no-print-directory
	@$(RM) $(OBJS) $(DEPS)
	@printf "\033[1;33m[$(NAME) objects files cleaned]\033[0m\n"

fclean:
	@$(MAKE) -C libft fclean --no-print-directory
	@$(RM) $(OBJS) $(DEPS)
	@printf "\033[1;33m[$(NAME) objects files cleaned]\033[0m\n"
	@$(RM) $(NAME)
	@printf "\033[1;35m[$(NAME) binary deleted]\033[0m\n"

re: fclean all

fclean_nolib:
	@$(RM) $(OBJS) $(DEPS)
	@printf "\033[1;33m[$(NAME) objects files cleaned]\033[0m\n"
	@$(RM) $(NAME)
	@printf "\033[1;35[$(NAME) binary deleted]\033[0m\n"

re_nolib: fclean_nolib all

lib_rule:
	@$(MAKE) -C libft --no-print-directory

.PHONY: lib_rule all clean fclean re re_nolib fclean_nolib
-include $(DEPS)
