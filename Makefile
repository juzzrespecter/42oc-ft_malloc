.PHONY:	all clean fclean re bonus


# ~~ source code, project layout mapping ~~ 

SRC_DIR=./src
OBJ_DIR=./obj
INC_DIR=./inc


SRC=malloc.c \
	realloc.c \
	free.c
OBJ=$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)$.o, $(SRC)) 
INC=$(addprefix $(INC_DIR), malloc.h)

# ~~                

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME=libft_malloc_${HOSTTYPE}.so

all: $(NAME)

$(NAME):
	@echo "i am a placeholder : - )"

test: src/test.c
	$(CC) $(FLAGS) src/test.c -o test

clean:
	${RM} ${OBJ_DIR}

fclean: clean
	${RM} ${NAME}

re: fclean all