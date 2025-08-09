#ifndef DEFINES_H
# define DEFINES_H

# define TRUE 1
# define FALSE 0
# define FAIL 999

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/* Colors */
#define GREEN	"\033[0;32m"
#define BLUE	"\033[0;34m"
#define RESET	"\033[0m"

# define PROMPT "\x1b[1;32mminishell$\x1b[0m  "
# define PROMPT_WO_DOLLAR GREEN "minishell > " RESET
# define DOLLAR_SIGN "$ "
# define MAX_TOKENS 1024

/* File */
# define PERMISSION 0644


# define EXIT "exit"

#endif