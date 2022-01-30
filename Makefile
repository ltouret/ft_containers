# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/21 14:41:56 by ltouret           #+#    #+#              #
#    Updated: 2022/01/30 19:34:49 by ltouret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES:
.SUFFIXES: .c .o

SHELL		= /bin/sh

NAME		= a.out

SRCS		= main.cpp

OBJS		= $(SRCS:.cpp=.o)

CPPC		= clang++

RM			= rm -f

CPPFLAGS	= -Wall -Wextra -Werror -std=c++98

all:	${NAME}

%.o: %.cpp
		${CPPC} ${CPPFLAGS} -c $< -o $@

$(NAME): ${OBJS}
		${CPPC} ${OBJS} -o ${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

test:	all
		./$(NAME)

.PHONY : all clean fclean re test
