# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/26 07:22:48 by yeongo            #+#    #+#              #
#    Updated: 2023/04/08 06:44:06 by yeongo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	philo
PROJECT_NAME	:=	PHILOSOPHERS

CC				:=	cc
CFLAGS			:=	-Wall -Wextra -Werror
CPPFLAGS		:=
MJFLAGS			 =	-MJ $@.part.json
RM				:=	rm -rf

HEADER			:=	./include/
SRC_DIR			:=	./src/
OBJ_DIR			:=	./.obj/
CACHE_DIR		:=	./.cache/

SRC_FILES		:=	$(addsuffix .c,			\
	 				ft_atoi					\
	 				ft_ctype				\
	 				ft_memory				\
	 				ft_string				\
	 				message					\
	 				parser					\
	 				init					\
					take_fork				\
	 				eat_action				\
	 				get_down_fork			\
	 				action					\
	 				monitor					\
					routine					\
					thread					\
	 				main					\
					)
OBJ_FILES		:=	$(SRC_FILES:.c=.o)
JSON_FILES		:=	compile_commands.json
SRC				:=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ				:=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

CPPFLAGS		+=	-I$(HEADER)
SRC_FOLDER		:=	$(SRC_DIR)
OBJ_FOLDER		:=	$(OBJ_DIR)
OBJS			:=	$(OBJ)
PRINT			:=	$(PROJECT_NAME)

ifdef TEST
		SRC				+=	$(addprefix $(SRC_DIR), $(addsuffix .c, print_test))
		OBJ				+=	$(addprefix $(OBJ_DIR), $(addsuffix .o, print_test))
		PRINT			:=	$(addsuffix _TEST, $(PRINT))
else ifdef DEBUG
		DBFLAGS			:=	-g -fsanitize=undefined,thread
		PRINT			:=	$(addsuffix _DEBUG, $(PRINT))
endif

.PHONY	:	all
all		:	$(OBJ_FOLDER) $(NAME)

$(OBJ_FOLDER)	:
	@if [ ! -d $(OBJ_FOLDER) ]; then \
		mkdir -p $(OBJ_FOLDER); \
	fi

$(NAME)	:	$(OBJS)
	@$(CC) $(LDFLAGS) $(DBFLAGS) -o $@ $^
	@(printf [ && find . -name "*.part.json" | xargs cat && printf ]) > $(JSON_FILES);
	@echo "\033[01;32m         SUCCESS!        \033[0m"

$(OBJ_FOLDER)%.o	:	$(SRC_FOLDER)%.c
	@$(CC) $(CFLAGS) $(DBFLAGS) $(CPPFLAGS) $(LDFLAGS) $(MJFLAGS) -c -o $@ $<

.PHONY	:	test
test	:
	@make TEST=1 all

.PHONY	:	debug
debug	:
	@make DEBUG=1 all

.PHONY	:	clean
clean	:
	@$(RM) $(OBJ_DIR) $(CACHE_DIR)
	@echo "\033[91m      REMOVE OBJECT      \033[0m"

.PHONY	:	fclean
fclean	:	clean
	@$(RM) $(NAME)
	@echo "\033[91m       FCLEAN DONE       \033[0m"

.PHONY	:	re
re		:	fclean
	@make all
