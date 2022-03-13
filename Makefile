# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 23:08:32 by ltouret           #+#    #+#              #
#    Updated: 2022/03/13 23:42:24 by ltouret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VECTOR	=		ft_vector
VECTOR2	=		std_vector
MAP		=		ft_map
MAP2	=		std_map
STACK	=		ft_stack
STACK2	=		std_stack
SET		=		ft_set
SET2	=		std_set

ALL	=	$(VECTOR) $(VECTOR2) $(MAP) $(MAP2) $(STACK) $(STACK2) $(SET) $(SET2)

RM = 	rm -rf

CXX =		clang++
CFLAGS =	-Wall -Werror -Wextra -std=c++98 #-fsanitize=address -g3

V_SRCS =		main_vector.cpp
M_SRCS =		main_map.cpp
S_SRCS =		main_stack.cpp
ST_SRCS =		main_set.cpp

INCLUDES =		vector.hpp map.hpp stack.hpp set.hpp

V_OBJS =		$(V_SRCS:%.cpp=%.o)
M_OBJS =		$(M_SRCS:%.cpp=%.o)
S_OBJS =		$(S_SRCS:%.cpp=%.o)
ST_OBJS =		$(ST_SRCS:%.cpp=%.o)


all: 			ft_vector ft_map ft_stack ft_set

clean:
				$(RM) $(V_OBJS) $(M_OBJS) $(S_OBJS) $(ST_OBJS)
				$(RM) *ft *std 

fclean:			clean
				$(RM) $(ALL)

re:				fclean all

.PHONY:			all clean fclean re test ft std vector map stack set

%.o: %.cpp $(INCLUDES)
	@$(CXX) $(CFLAGS) -c $< -o $@

ft_vector: $(V_OBJS)
	$(CXX) $(CFLAGS) -D FT $? -o $(VECTOR)

std_vector: $(V_SRCS)
	$(CXX) $(CFLAGS) -D STD $? -o $(VECTOR2)

vector:
	@$(RM) $(VECTOR)
	@$(RM) $(VECTOR2)
	@make -s ft_vector
	./$(VECTOR) > vft
	@make -s std_vector
	./$(VECTOR2) > vstd
	diff -s vft vstd

ft_map: $(M_OBJS)
	$(CXX) $(CFLAGS) -D FT $? -o $(MAP)

std_map: $(M_SRCS)
	$(CXX) $(CFLAGS) -D STD $? -o $(MAP2)

map:
	@$(RM) $(MAP)
	@$(RM) $(MAP2)
	@make -s ft_map
	./$(MAP) > mft
	@make -s std_map
	./$(MAP2) > mstd
	diff -s mft mstd

ft_stack: $(S_OBJS)
	$(CXX) $(CFLAGS) -D FT $? -o $(STACK)

std_stack: $(S_SRCS)
	$(CXX) $(CFLAGS) -D STD $? -o $(STACK2)

stack:
	@$(RM) $(STACK)
	@$(RM) $(STACK2)
	@make -s ft_stack
	./$(STACK) > sft
	@make -s std_stack
	./$(STACK2) > sstd
	diff -s sft sstd

ft_set: $(ST_OBJS)
	$(CXX) $(CFLAGS) -D FT $? -o $(SET)

std_set: $(ST_SRCS)
	$(CXX) $(CFLAGS) -D STD $? -o $(SET2)

set:
	@$(RM) $(SET)
	@$(RM) $(SET2)
	@make -s ft_set
	./$(SET) > stft
	@make -s std_set
	./$(SET2) > ststd
	diff -s stft ststd
