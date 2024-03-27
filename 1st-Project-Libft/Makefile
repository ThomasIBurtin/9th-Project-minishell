CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_calloc.c \
      ft_memset.c \
      ft_strdup.c \
      ft_strlcat.c \
      ft_strlcpy.c \
      ft_strlen.c \
      ft_strjoin.c \
      ft_substr.c \
      ft_strchr.c \
      ft_putchar_fd.c \
      ft_putstr_fd.c \
      ft_putendl_fd.c \
      ft_split.c \
      ft_lstnew.c \
      ft_lstadd_back.c \
      ft_strnstr.c \
      ft_compare.c

OBJ = $(SRC:.c=.o)
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:     clean
	rm -f $(NAME)

re:   fclean all





