# ================================ SETTINGS ================================= #

NAME			= minishell
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g
INCLUDES		= -I./includes -I./libft -I/opt/homebrew/opt/readline/include
LIBS			= -lreadline -L./libft -lft -L/opt/homebrew/opt/readline/lib

# =============================== DIRECTORIES =============================== #

SRCDIR			= srcs
OBJDIR			= obj
LIBFTDIR		= libft
INCDIR			= includes

# ================================ MODULES ================================== #

# Main application
MAIN_DIR		= $(SRCDIR)/main
MAIN_SRCS		= init_env.c \
				  init.c \
				  main.c \
				  process_command.c \
				  prompt.c \
				  shell_loop.c

# Executer module
EXEC_DIR		= $(SRCDIR)/executer
EXEC_SRCS		= executer.c \
				  multiple_command.c \
				  redirections.c \
				  single_command.c \
				  utils.c

# Heredoc module
HD_DIR			= $(SRCDIR)/executer/heredoc
HD_SRCS			= heredoc_handler.c \
				  heredoc_child.c \
				  heredoc_parent.c

# Command module
CMD_DIR			= $(SRCDIR)/executer/command
CMD_SRCS		= cmd_builder.c \
				  cmd_filler.c \
				  cmd_utils.c

# Built-ins module
BUILTIN_DIR		= $(SRCDIR)/executer/builtins
BUILTIN_SRCS	= builtins_basics.c \
				   builtins_cd.c \
				   builtins_echo.c \
				   builtins_exit.c \
				   builtins_export.c \
				   builtins_unset.c \
				   builtins_utils.c \
				   builtins_utils2.c

# Signal handling
SIGNAL_DIR		= $(SRCDIR)/signal
SIGNAL_SRCS		= signals.c \
				  signals_2.c

# Cleanup tools
CLEANUP_DIR		= $(SRCDIR)/cleanup_tools
CLEANUP_SRCS	= free_command.c \
				  free_env.c \
				  free_pipeline.c \
				  free.c \
				  close_fds.c \
				  free_builtins.c

# Error handling
ERROR_DIR		= $(SRCDIR)/error
ERROR_SRCS		= errors.c

# Test creators (Mock data)
TEST_DIR		= $(SRCDIR)
TEST_SRCS		= temp_creator.c \
				  temp_creator_redir_in.c \
				  temp_creator_redir_out.c \
				  temp_creator_redir_append.c \
				  temp_creator_multiple_heredoc.c \
				  temp_creator_heredoc_plus_append.c \
				  temp_creator_builtins_pwd.c \
				  temp_creator_builtins_echo.c \
				  temp_creator_builtins_env.c \
				  temp_creator_builtins_exit.c \
				  temp_creator_builtins_cd.c \
				  temp_creator_builtins_unset.c \
				  temp_creator_builtins_export.c \
				  temp_creator_heredoc_normal.c \
				  temp_creator_heredoc_redirection.c \
				  print_shell_info.c

# ============================== FILE PATHS =============================== #

# Generate full paths for source files
MAIN_FILES		= $(addprefix $(MAIN_DIR)/, $(MAIN_SRCS))
EXEC_FILES		= $(addprefix $(EXEC_DIR)/, $(EXEC_SRCS))
HD_FILES		= $(addprefix $(HD_DIR)/, $(HD_SRCS))
CMD_FILES		= $(addprefix $(CMD_DIR)/, $(CMD_SRCS))
BUILTIN_FILES	= $(addprefix $(BUILTIN_DIR)/, $(BUILTIN_SRCS))
SIGNAL_FILES	= $(addprefix $(SIGNAL_DIR)/, $(SIGNAL_SRCS))
CLEANUP_FILES	= $(addprefix $(CLEANUP_DIR)/, $(CLEANUP_SRCS))
ERROR_FILES		= $(addprefix $(ERROR_DIR)/, $(ERROR_SRCS))
TEST_FILES		= $(addprefix $(TEST_DIR)/, $(TEST_SRCS))

# Combine all source files
ALL_SRCS		= $(MAIN_FILES) $(EXEC_FILES) $(HD_FILES) $(CMD_FILES) $(BUILTIN_FILES) \
				  $(SIGNAL_FILES) $(CLEANUP_FILES) $(ERROR_FILES) $(TEST_FILES)

# Generate object files
OBJS			= $(ALL_SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# ================================= COLORS =================================== #

RED				= \033[0;31m
GREEN			= \033[0;32m
YELLOW			= \033[0;33m
BLUE			= \033[0;34m
PURPLE			= \033[0;35m
CYAN			= \033[0;36m
WHITE			= \033[1;37m
RESET			= \033[0m

# ================================= RULES =================================== #

all: header $(NAME)

header:
	@echo "$(CYAN)"
	@echo "╔══════════════════════════════════════════════════════════════════════════════╗"
	@echo "║                                 MINISHELL                                    ║"
	@echo "║                            Building Project...                              ║"
	@echo "╚══════════════════════════════════════════════════════════════════════════════╝"
	@echo "$(RESET)"

$(NAME): libft $(OBJS)
	@echo "$(GREEN)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(RESET)"
	@echo "$(WHITE)Usage: ./$(NAME)$(RESET)"

libft:
	@echo "$(YELLOW)📚 Building libft...$(RESET)"
	@make -C $(LIBFTDIR) --no-print-directory

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)🔨 Compiling $(notdir $<)...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ============================== CLEAN RULES =============================== #

clean:
	@echo "$(YELLOW)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@make -C $(LIBFTDIR) clean --no-print-directory
	@echo "$(GREEN)✅ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)🗑️  Removing executable...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean --no-print-directory
	@echo "$(GREEN)✅ Full clean completed!$(RESET)"

re: fclean all

# ============================== UTILITY RULES ============================== #

norm:
	@echo "$(PURPLE)📏 Checking norminette...$(RESET)"
	@norminette $(SRCDIR)/ $(INCDIR)/ | grep -v "OK!" || echo "$(GREEN)✅ All files pass norminette!$(RESET)"

bonus: all

# Development helpers
debug: CFLAGS += -g -fsanitize=address
debug: re
	@echo "$(CYAN)🐛 Debug build completed with AddressSanitizer$(RESET)"

leaks: all
	@echo "$(CYAN)🔍 Running with leak detection...$(RESET)"
	@leaks --atExit -- ./$(NAME)

valgrind: all
	@echo "$(CYAN)🔍 Running with valgrind...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

# Show compilation info
info:
	@echo "$(WHITE)📋 Compilation Information:$(RESET)"
	@echo "$(CYAN)Compiler:$(RESET) $(CC)"
	@echo "$(CYAN)Flags:$(RESET) $(CFLAGS)"
	@echo "$(CYAN)Includes:$(RESET) $(INCLUDES)"
	@echo "$(CYAN)Libraries:$(RESET) $(LIBS)"
	@echo "$(CYAN)Source files:$(RESET) $(words $(ALL_SRCS))"
	@echo "$(CYAN)Object files:$(RESET) $(words $(OBJS))"

# Module-specific builds (for development)
build-main: $(addprefix $(OBJDIR)/, $(MAIN_FILES:$(SRCDIR)/%.c=%.o))
	@echo "$(GREEN)✅ Main module compiled!$(RESET)"

build-executer: $(addprefix $(OBJDIR)/, $(EXEC_FILES:$(SRCDIR)/%.c=%.o))
	@echo "$(GREEN)✅ Executer module compiled!$(RESET)"

build-heredoc: $(addprefix $(OBJDIR)/, $(HD_FILES:$(SRCDIR)/%.c=%.o))
	@echo "$(GREEN)✅ Heredoc module compiled!$(RESET)"

build-command: $(addprefix $(OBJDIR)/, $(CMD_FILES:$(SRCDIR)/%.c=%.o))
	@echo "$(GREEN)✅ Command module compiled!$(RESET)"

build-builtins: $(addprefix $(OBJDIR)/, $(BUILTIN_FILES:$(SRCDIR)/%.c=%.o))
	@echo "$(GREEN)✅ Built-ins module compiled!$(RESET)"

# Help
help:
	@echo "$(WHITE)🆘 Available targets:$(RESET)"
	@echo "$(CYAN)  all$(RESET)           - Build the project"
	@echo "$(CYAN)  clean$(RESET)         - Remove object files"
	@echo "$(CYAN)  fclean$(RESET)        - Remove object files and executable"
	@echo "$(CYAN)  re$(RESET)            - Rebuild the project"
	@echo "$(CYAN)  norm$(RESET)          - Check norminette"
	@echo "$(CYAN)  debug$(RESET)         - Build with debug flags and AddressSanitizer"
	@echo "$(CYAN)  leaks$(RESET)         - Run with leak detection (macOS)"
	@echo "$(CYAN)  valgrind$(RESET)      - Run with valgrind (Linux)"
	@echo "$(CYAN)  info$(RESET)          - Show compilation information"
	@echo "$(CYAN)  help$(RESET)          - Show this help message"
	@echo "$(CYAN)  build-main$(RESET)     - Build only main module"
	@echo "$(CYAN)  build-executer$(RESET) - Build only executer module"
	@echo "$(CYAN)  build-heredoc$(RESET)  - Build only heredoc module"
	@echo "$(CYAN)  build-command$(RESET)  - Build only command module"
	@echo "$(CYAN)  build-builtins$(RESET) - Build only built-ins module"

.PHONY: all clean fclean re norm bonus debug leaks valgrind info help header libft \
		build-main build-executer build-heredoc build-command build-builtins