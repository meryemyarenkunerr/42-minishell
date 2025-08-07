NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES_M	= -I./includes -I./libft -I/opt/homebrew/opt/readline/include
LIBS_M		= -lreadline -L./libft -lft -L/opt/homebrew/opt/readline/lib

# Directories
SRCDIR		= srcs
OBJDIR		= obj
LIBFTDIR	= libft

# Executables
SRCS		= $(SRCDIR)/main.c \
			  $(SRCDIR)/env_utils.c \
			  $(SRCDIR)/init_shell.c \
			  $(SRCDIR)/free.c \
			  $(SRCDIR)/shell_loop.c \
			  $(SRCDIR)/signals.c \
			  $(SRCDIR)/prompt_utils.c \
			  $(SRCDIR)/advanced_lexer.c \
			  $(SRCDIR)/improved_expander.c \
			  $(SRCDIR)/quote_remover.c \
			  $(SRCDIR)/post_expander.c \
			  $(SRCDIR)/parser.c \
			  $(SRCDIR)/lexer.c \
			  $(SRCDIR)/utils.c \
			  $(SRCDIR)/pipeline_tokenizer.c \
			  $(SRCDIR)/token_classifier.c \
			  $(SRCDIR)/executer.c \
			  $(SRCDIR)/temp_creator.c \
			  $(SRCDIR)/redirections.c \
			  $(SRCDIR)/heredoc.c \

# Object Files
OBJS		= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Colors
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
PURPLE		= \033[0;35m
CYAN		= \033[0;36m
RESET		= \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@make -C $(LIBFTDIR)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LIBS_M) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES_M) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@make -C $(LIBFTDIR) clean

fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all

norm:
	@echo "$(PURPLE)Checking norminette...$(RESET)"
	@norminette $(SRCDIR)/ includes/

.PHONY: all clean fclean re
