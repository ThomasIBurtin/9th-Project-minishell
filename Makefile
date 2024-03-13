CC = gcc
CFLAGS = -Werror -Wall -Wextra
SRC = main.c \
	  init_free.c \
	  parsing/parse.c \
	  parsing/token.c \
	  parsing/data.c \
	  parsing/variable.c \
	  parsing/utils_data.c \
	  parsing/utils_variable.c \
      execution/exec.c
OBJ = $(SRC:.c=.o)
LIBFT_OBJ = 1st-Project-Libft/*.o 
NAME = minishell

all: libft_bibliotheque $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBFT_OBJ) -lreadline

%.o: %.c
	$(CC) -c $< -o $@

libft_bibliotheque:
	$(MAKE) -C 1st-Project-Libft

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C 1st-Project-Libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C 1st-Project-Libft

re: fclean all