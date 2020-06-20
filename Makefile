NAME		=	ft_strace
FLAGS		= 	#-Wall -Werror -Wextra
COMPILER	=	gcc

DIR_INC		=	./inc/
DIR_SRC		=	./src/
DIR_OBJ		= 	./obj/

HEADERS		=	get_data.h \
				opt_parser.h.h \
				print.h \
				syscall.h \
				trace.h \
				resolve_path.h \
				errno_str.h

SRC			=	ft_strace.c \
				trace.c \
				opt_parser.c \
				print.c \
				syscall.c \
				get_data.c \
				resolve_path.c \
				errno.c

INC_PATH 	= 	$(addprefix $(DIR_INC), $(HEADERS))

OBJ 		= 	$(addprefix $(DIR_OBJ), $(SRC:.c=.o))
INC 		= 	$(addprefix -I, $(DIR_INC))

.PHONY: all obj $(NAME) clean fclean re

all: obj $(NAME)

obj:
	@mkdir -p $(DIR_OBJ)

$(NAME): $(OBJ)
	@$(COMPILER) -o $(NAME) $(OBJ)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@$(COMPILER) $(FLAGS) $(INC) -c -o $@ $<

clean:
	@rm -rf $(DIR_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all