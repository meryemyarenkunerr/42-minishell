# 42cursus - libft

This project involves developing a custom C library that includes essential functions, which you’ll be allowed to reuse in all other projects within the cursus.  

For more detailed information, refer to the project’s official documentation.   

## Functions  

### Functions from `<ctype.h>`  
- `ft_isalpha` – Checks if a character is alphabetic.
- `ft_isdigit` – Checks if a character is a digit.
- `ft_isalnum` – Tests whether a character is alphanumeric.  
- `ft_isascii` – Checks if a character is an ASCII character.
- `ft_isprint` – Tests for printable characters (including spaces).   
- `ft_tolower` – Converts uppercase letters to lowercase.  
- `ft_toupper` – Converts lowercase letters to uppercase.

### Functions from `<string.h>`  
- `ft_strlen` – Calculates the length of a string.
- `ft_memset` – Writes a byte to a memory block.
- `ft_memcpy` – Copies a memory area.
- `ft_memmove` – Copies a memory block.
- `ft_strlcpy` – Copies a string with size-limitation.  
- `ft_strlcat` – Concatenates strings with size-limitation.
- `ft_strchr` – Finds the first occurrence of a character in a string.  
- `ft_strrchr` – Finds the last occurrence of a character in a string.
- `ft_strncmp` – Compares two strings up to a specified number of characters.
- `ft_memchr` – Finds a byte in a memory block.  
- `ft_memcmp` – Compares two memory blocks.  
- `ft_strnstr` – Finds a substring within a bounded string.  
- `ft_strdup` – Creates a duplicate of a string.  

### Functions from `<strings.h>`  
- `ft_bzero` – Writes zeroes to a byte string.

### Functions from `<stdlib.h>`  
- `ft_atoi` – Converts an ASCII string to an integer.  
- `ft_calloc` – Allocates memory and initializes it to zero.    

### Non-standard Utility Functions  
- `ft_substr` - Allocates and returns a substring from the string.
- `ft_strjoin` – Concatenates two strings into a new dynamically allocated string.
- `ft_strtrim` - Trim beginning and end of string with the specified characters.
- `ft_split` – Splits a string into an array of substrings using a specified delimiter.
- `ft_itoa` – Converts an integer to a string.
- `ft_strmapi` - Create new string from modifying string with specified function.
- `ft_striter` - Apply the function on each character of the string passed as argument.
- `ft_putchar_fd` – Outputs a character to the given file descriptor.
- `ft_putstr_fd` – Outputs a string to the given file descriptor.
- `ft_putendl_fd` – Outputs a string to the given file descriptor followed by a new line. 
- `ft_putnbr_fd` – Outputs an integer to the given file descriptor. 

### Linked List Functions - Bonus Part
- `ft_lstnew` – Creates a new linked list node.
- `ft_lstadd_front` – Adds a new node to the beginning of a list.  
- `ft_lstsize` – Counts the number of nodes in a list.  
- `ft_lstlast` – Finds the last node in a list.  
- `ft_lstadd_back` – Adds a new node to the end of a list.  
- `ft_lstdelone` – Frees the node’s content and the node, without freeing next.
- `ft_lstclear` – Deletes nodes starting from a specified point in a list.  
- `ft_lstiter` – Applies a function to the content of each node in a list.  
- `ft_lstmap` – Creates a new list by applying a function to the content of each node in an existing list.  
