NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES_M	= -I./includes -I./libft -I/opt/homebrew/opt/readline/include
LIBS_M		= -lreadline -L./libft -lft -L/opt/homebrew/opt/readline/lib

# Directories
SRCDIR		= srcs
OBJDIR		= obj
LIBFTDIR	= libft

# Source files
SRCS 		= srcs/cleanup_tools/free.c \
			  srcs/error/errors.c \
			  srcs/executer/executer.c \
			  srcs/executer/cmd_filler.c \
			  srcs/executer/cmd_controller.c \
			  srcs/executer/cmd_setter.c \
			  srcs/executer/heredoc_filler.c \
			  srcs/main/init.c \
			  srcs/main/main.c \
			  srcs/main/prompt.c \
			  srcs/main/utils.c \
			  srcs/main/shell_loop.c \
			  srcs/main/process_command.c \
			  srcs/parser_lexer/advanced_lexer.c \
			  srcs/parser_lexer/improved_expander.c \
			  srcs/parser_lexer/lexer.c \
			  srcs/parser_lexer/parser.c \
			  srcs/parser_lexer/pipeline_tokenizer.c \
			  srcs/parser_lexer/post_expander.c \
			  srcs/parser_lexer/quote_remover.c \
			  srcs/parser_lexer/token_classifier.c \
			  srcs/parser_lexer/utils.c \
			  srcs/signal/signals.c \
			  srcs/temp_creator.c \
			  srcs/temp_creator_redir_in.c \
			  srcs/temp_creator_redir_out.c \
			  srcs/temp_creator_redir_append.c \
			  srcs/temp_creator_multiple_heredoc.c \
			  srcs/temp_creator_heredoc_plus_append.c \

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
