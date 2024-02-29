# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 13:24:39 by marvin            #+#    #+#              #
#    Updated: 2024/01/10 13:24:39 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_ORANGE=\033[0;34m
COLOUR_END=\033[0m
COLOUR_YELLOW=\033[0;33m
COLOUR_CYAN=\033[0;36m

NAME	= webserver

RM				= rm -rf

SRC				=	srcs/main.cpp							\
					srcs/http/Http.cpp						\
					srcs/conf/conf.cpp						\
					# src/Http.cpp						\
					# src/Http.cpp						\
					# src/Http.cpp						\
					# src/Http.cpp						\


DIRS			= objs
OBJS_DIRS		= objs objs/srcs objs/srcs/http objs/srcs/conf
HEADERS			= includes
OBJS			= ${SRC:.cpp=.o}
CFLAGS 			= -I $(HEADERS) -Werror -Wextra -Wall -std=c++98 #-fsanitize=undefined
_OBJS			= $(addprefix $(DIRS)/, $(OBJS))


all: ${NAME}

${NAME}: ${_OBJS}
			@echo "$(COLOUR_CYAN)Compile..."
			c++ ${CFLAGS} $(_OBJS) -o $@
${DIRS}/%.o: %.cpp
		@mkdir -p $(OBJS_DIRS)
		c++ $(CFLAGS) -c $< -o $@ -g3
clean:
			$(RM) ${_OBJS}
			$(RM) objs

fclean:		clean
			$(RM) $(NAME) *.a
			$(RM) objs

re:			fclean all