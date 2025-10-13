NAME = a.out
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -fr
MAIN = src/main.c
FILES = src/Utils/*.c
#OBJ_SRC = loading.o loading2.o rendering.o rendering2.o rendering3.o moving.o \
		validating.o
#OBJ = obj/loading.o obj/loading2.o obj/rendering.o obj/rendering2.o obj/rendering3.o obj/moving.o \
		obj/validating.o
#LIBFT = ./libft
#WBLOCK = --no-print-directory

all: $(NAME)

$(NAME): $(OBJ)
#	@$(CC) $(FLAGS) $(OBJ) -L $(LIBFT) -lft -lm -o $(NAME)
	@$(CC) $(FLAGS) $(OBJ) -lm -o $(NAME)

$(OBJ): $(MAIN) $(FILES)
#	@make $(WBLOCK) -C $(LIBFT) all
	@mkdir -p obj
	@$(CC) $(FLAGS) -c $(FILES)
	@mv $(OBJ_SRC) obj/

clean:
	@$(RM) $(OBJ) obj
#	@make $(WBLOCK) clean -C $(LIBFT)

fclean:
	@$(RM) $(OBJ) $(NAME) obj
#	@make $(WBLOCK) fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re