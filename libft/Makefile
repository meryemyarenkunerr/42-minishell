NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
ARFLAGS = -rc

SRC = ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_isascii.c ft_isprint.c \
		ft_strchr.c ft_strlcat.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_tolower.c ft_toupper.c ft_strlcpy.c ft_atoi.c \
		ft_memset.c ft_memcpy.c ft_bzero.c ft_memchr.c ft_memcmp.c \
		ft_memmove.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_striteri.c ft_strmapi.c ft_strtrim.c ft_split.c ft_itoa.c \

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		ft_lstmap.c \

OBJ = $(SRC:.c=.o)
OBJB = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar $(ARFLAGS) $(NAME) $(OBJ)

bonus: $(OBJB)
	@ar $(ARFLAGS) $(NAME) $(OBJB)

clean:
	@$(RM) $(OBJ) $(OBJB)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
