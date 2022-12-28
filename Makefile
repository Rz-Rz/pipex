# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 14:25:53 by kdhrif            #+#    #+#              #
#    Updated: 2022/12/28 20:50:13 by kdhrif           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = pipex
SRCS_DIR = srcs
OBJS_DIR = objs
SRCS	:= $(shell find srcs/*.c -exec basename \ {} \;)
OBJS     = ${patsubst %.c,${OBJS_DIR}/%.o,${SRCS}}
CC       = gcc
CFLAGS   = -g3
LIB      = libft/libft.a
HEADERS  = pipex.h

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "\033[33mcompiling ${NAME}..."
	@echo "SRCS = ${SRCS}"
	@echo "OBJS = ${OBJS}"

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@${CC} ${CFLAGS} -c $< -o $@

${LIB} :
	@make -C libft

${NAME}: $(LIB) $(OBJS_DIR) $(OBJS) ${HEADERS}
	$(CC) $(OBJS) ${LIB} -o $(NAME)
	@echo "\033[32m$ ${NAME} compiled !"

clean:
	make -C libft clean
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

# valgrind: all
# 	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY:	all clean fclean re
