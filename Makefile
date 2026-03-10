.PHONY:	all clean fclean re bonus

# ~~  ~~ 

SRC_DIR=src
OBJ_DIR=obj
INC_DIR=inc


SRC:=malloc.c \
	realloc.c \
	free.c
OBJ:=$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC)) 
INC:=$(addprefix $(INC_DIR), malloc.h)

vpath %.c $(SRC_DIR)

CC:=gcc
CFLAGS:=-Wall -Werror -Wextra -fPIC
LDFLAGS:=-shared        

RM:=rm -rfv
MKDIR:=mkdir -pv

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME=libft_malloc_$(HOSTTYPE).so

# ~~ ~~       

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $< -c -o $@

$(OBJ_DIR):
	mkdir -pv $@

test: src/test.c
	$(CC) src/test.c -g3 -o test -L. -lft_malloc_$(HOSTTYPE)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# ~~ Test suite temporal ~~
.PHONY: trace_test microtest ultratest access_test
trace_test:
microtest:
ultratest:
access_test: