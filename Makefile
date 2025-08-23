# ================================ SETTINGS ================================= #

NAME			= minishell
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address
INCLUDES		= -I./includes -I./libft
LIBS			= -L./libft -lft

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	# macOS için (brew readline kullanıyorsan path ekleniyor)
	INCLUDES	+= -I$(shell brew --prefix readline)/include
	LIBS		+= -L$(shell brew --prefix readline)/lib -lreadline -lhistory -lncurses
else
	# Linux için
	LIBS		+= -lreadline
endif
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
				  heredoc_parent.c \
				  heredoc_utils.c \
				  heredoc_safe_readline.c

# Command module
CMD_DIR			= $(SRCDIR)/executer/command
CMD_SRCS		= command_builder.c \
				  command_creation.c \
				  heredoc_management.c \
				  utils.c \
				  utils2.c \
				  token_analysis.c \
				  expander.c

# Built-ins module
BUILTIN_DIR		= $(SRCDIR)/executer/builtins
BUILTIN_SRCS	= builtins_basics.c \
				  builtins_cd.c \
				  builtins_echo.c \
				  builtins_exit.c \
				  builtins_export.c \
				  builtins_export_util.c \
				  builtins_unset.c \
				  builtins_utils.c \
				  builtins_utils2.c

# External module
EXTERNAL_DIR	= $(SRCDIR)/executer/external
EXTERNAL_SRCS	= external.c \
				  child_utils.c \
				  external_child.c \
				  path.c

# Multiple module
MULTIPLE_DIR	= $(SRCDIR)/executer/multiple
MULTIPLE_SRCS	= pipeline.c \
				  pipeline_child.c \
				  pipeline_external.c \
				  multiple_utils.c

# Signal handling
SIGNAL_DIR		= $(SRCDIR)/signal
SIGNAL_SRCS		= signals.c \
				  heredoc_signal.c

# Cleanup tools
CLEANUP_DIR		= $(SRCDIR)/cleanup_tools
CLEANUP_SRCS	= free_command.c \
				  free_env.c \
				  free_pipeline.c \
				  free.c \
				  close_fds.c \
				  free_builtins.c \
				  close_pipes.c \
				  free_pipes.c \
				  free_heredoc.c

# PARSER
M_PARSER_DIR		= $(SRCDIR)/parser
M_PARSER_SRCS		= router_parser.c

# Advanced lexer
A_LEXER_DIR		= $(SRCDIR)/parser/advanced_lexer
A_LEXER_SRCS	= advanced_lexer.c \
				  advanced_lexer_utils.c \
				  advanced_lexer_utils_two.c \
				  advanced_lexer_utils_three.c

# Check redirects
C_REDIRECT_DIR	= $(SRCDIR)/parser/check_redirects
C_REDIRECT_SRCS	= check_redirects.c

# EOF check
EOF_CHECK_DIR	= $(SRCDIR)/parser/eof_check
EOF_CHECK_SRCS	= eof_check.c

# Improved expander
I_EXPANDER_DIR	= $(SRCDIR)/parser/improved_expander
I_EXPANDER_SRCS	= improved_expander.c \
				  improved_expander_utils.c

# Parser
PARSER_DIR		= $(SRCDIR)/parser/parser
PARSER_SRCS		= parser.c \
				  parser_utils.c

# Pipeline tokenizer
P_TOKEN_DIR		= $(SRCDIR)/parser/pipline_tokenizer
P_TOKEN_SRCS	= pipeline_tokenizer.c \
				  pipeline_tokenizer_utils.c

# Post expander
POST_EXPANDER_DIR	= $(SRCDIR)/parser/post_expander
POST_EXPANDER_SRCS	= post_expander.c \
					  post_expander_utils.c

# Quote remover
Q_REMOVE_DIR	= $(SRCDIR)/parser/quote_remover
Q_REMOVE_SRCS	= quote_remover.c

# Syntax check
S_CHECK_DIR		= $(SRCDIR)/parser/syntax_check
S_CHECK_SRCS	= syntax_check.c

# Token classifier
T_CLASS_DIR		= $(SRCDIR)/parser/token_classifier
T_CLASS_SRCS	= token_classifier.c

# Error handling
ERROR_DIR		= $(SRCDIR)/error
ERROR_SRCS		= errors.c \
				  builtins_error.c \
				  heredoc_error.c \
				  syntax_error.c

# Test creators (Mock data)
TEST_DIR		= $(SRCDIR)
TEST_SRCS		= print_shell_info.c

# ============================== FILE PATHS =============================== #

# Generate full paths for source files
MAIN_FILES			= $(addprefix $(MAIN_DIR)/, $(MAIN_SRCS))
EXEC_FILES			= $(addprefix $(EXEC_DIR)/, $(EXEC_SRCS))
HD_FILES			= $(addprefix $(HD_DIR)/, $(HD_SRCS))
CMD_FILES			= $(addprefix $(CMD_DIR)/, $(CMD_SRCS))
BUILTIN_FILES		= $(addprefix $(BUILTIN_DIR)/, $(BUILTIN_SRCS))
EXTERNAL_FILES		= $(addprefix $(EXTERNAL_DIR)/, $(EXTERNAL_SRCS))
MULTIPLE_FILES		= $(addprefix $(MULTIPLE_DIR)/, $(MULTIPLE_SRCS))
SIGNAL_FILES		= $(addprefix $(SIGNAL_DIR)/, $(SIGNAL_SRCS))
CLEANUP_FILES		= $(addprefix $(CLEANUP_DIR)/, $(CLEANUP_SRCS))
ERROR_FILES			= $(addprefix $(ERROR_DIR)/, $(ERROR_SRCS))
TEST_FILES			= $(addprefix $(TEST_DIR)/, $(TEST_SRCS))
A_LEXER_FILES		= $(addprefix $(A_LEXER_DIR)/, $(A_LEXER_SRCS))
C_REDIRECT_FILES	= $(addprefix $(C_REDIRECT_DIR)/, $(C_REDIRECT_SRCS))
EOF_CHECK_FILES		= $(addprefix $(EOF_CHECK_DIR)/, $(EOF_CHECK_SRCS))
I_EXPANDER_FILES	= $(addprefix $(I_EXPANDER_DIR)/, $(I_EXPANDER_SRCS))
PARSER_FILES		= $(addprefix $(PARSER_DIR)/, $(PARSER_SRCS))
P_TOKEN_FILES		= $(addprefix $(P_TOKEN_DIR)/, $(P_TOKEN_SRCS))
POST_EXPANDER_FILES	= $(addprefix $(POST_EXPANDER_DIR)/, $(POST_EXPANDER_SRCS))
Q_REMOVE_FILES		= $(addprefix $(Q_REMOVE_DIR)/, $(Q_REMOVE_SRCS))
S_CHECK_FILES		= $(addprefix $(S_CHECK_DIR)/, $(S_CHECK_SRCS))
T_CLASS_FILES		= $(addprefix $(T_CLASS_DIR)/, $(T_CLASS_SRCS))
M_PARSER_FILES		= $(addprefix $(M_PARSER_DIR)/, $(M_PARSER_SRCS))

# Combine all source files
ALL_SRCS		= $(MAIN_FILES) $(EXEC_FILES) $(HD_FILES) $(CMD_FILES) $(BUILTIN_FILES) \
				  $(EXTERNAL_FILES) $(SIGNAL_FILES) $(CLEANUP_FILES) $(ERROR_FILES) \
				  $(TEST_FILES) $(MULTIPLE_FILES) $(A_LEXER_FILES) $(C_REDIRECT_FILES) \
				  $(EOF_CHECK_FILES) $(I_EXPANDER_FILES) $(T_CLASS_FILES) $(M_PARSER_FILES) \
				  $(P_TOKEN_FILES) $(POST_EXPANDER_FILES) $(Q_REMOVE_FILES) $(S_CHECK_FILES)


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
	@$(CC) $(OBJS) $(LIBS) $(CFLAGS) -o $(NAME)
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

# ============================= NORMINETTE RULES ============================ #

NORM_FILES	= $(ALL_SRCS) $(wildcard $(INCDIR)/*.h)

norma:
	@echo "$(PURPLE)📏 Checking norminette...$(RESET)"
	@for file in $(NORM_FILES); do \
		echo ""; \
		echo "$(CYAN)──────────────────────────────────────────────$(RESET)"; \
		echo "$(YELLOW)📁 Checking: $(GREEN)$$file$(RESET)"; \
		output=$$(norminette $$file 2>&1); \
		if echo "$$output" | grep -q "Error\|Warning"; then \
			echo "$$output" | grep -v "^$$file" \
				| sed 's/Error:/$(RED)Error:$(RESET)/g' \
				| sed 's/Warning:/$(YELLOW)Warning:$(RESET)/g'; \
		else \
			echo "$(GREEN)✓ OK$(RESET)"; \
		fi; \
		echo "$(CYAN)──────────────────────────────────────────────$(RESET)"; \
	done
	@echo ""; \
	echo "$(PURPLE)✨ Norminette check completed! ✨$(RESET)"

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
