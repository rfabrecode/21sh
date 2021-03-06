# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/19 14:14:34 by jecarol           #+#    #+#              #
#    Updated: 2018/05/03 18:01:32 by jecarol          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = 21sh

CC = gcc

SRCS_LIST = main.c line_movement.c line_edit.c copy_paste.c term.c\
line_edit_more.c env.c history.c tokenizer.c parsing.c freesets.c\
execution.c path_mngmnt.c errors.c echo.c cd.c setenv.c unset.c signal.c\
fd.c pipes.c more_parsing.c tools.c redirections.c inits.c quotes.c\
quote_more.c cd_env.c env_misc.c env_tools.c execution_more.c free_more.c\
line_edit_misc.c line_edit_tools.c misc.c ast_builder.c heredoc.c\
parsing_checking.c parsing_tools.c init_more.c redirections_more.c\
split_21.c split_21_tools.c tools_more.c lol.c parsing_misc.c\
line_movement_more.c misc_more.c parsing_misc_more.c

SRCS_DIR = srcs/
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR = objs/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIST))

HEADERS = -I./libft -I./includes

LIB = -L./libft -lft

# COLOR
C_GOOD = "\033[32m"
C_DURING = "\033[36m"

# MESSAGE
SUCCESS = $(C_GOOD)COMPILATION SUCCEEDED

all: $(NAME)

$(NAME): $(OBJS) includes/sh.h
	@make -C ./libft/
	@echo $(C_DURING)"Compiling" [ $(NAME) . . . ]
	@$(CC) $(CFLAGS) -ltermcap $(OBJS) $(LIB) -o $(NAME)
	@echo $(SUCCESS)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c includes/sh.h
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
		@/bin/rm -rf $(OBJS_DIR)
		@make clean -C libft/
		@echo $(C_GOOD)"OBJ FILES DELETED"

fclean: clean
		@/bin/rm -rf $(NAME)
		@make fclean -C libft/
		@echo $(C_GOOD)"EXECUTABLE FILE DELETED"

re: fclean all

lldb:
			gcc $(SRCS) $(LIB) -g -ltermcap -o $(NAME)

sanitize:
			gcc $(SRCS) $(LIB) -g3 -fsanitize=address -ltermcap -o $(NAME)
