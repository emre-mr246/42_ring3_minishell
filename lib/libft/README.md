<div align="center">
  <img src="img/libft.png" alt="Logo" width="150" height="150">
  <h2>42 LIBFT PROJECT</h2>
    <a href= https://github.com/emre-mr246/42-evaluation><img src="https://img.shields.io/badge/score-125%20%2F%20100-success?style=for-the-badge"/></a>
    <a href= https://github.com/emre-mr246/42-evaluation><img src="https://img.shields.io/badge/circle-0-magenta?style=for-the-badge"/></a>
    <a href= https://github.com/emre-mr246/42-evaluation><img src="https://img.shields.io/badge/42-Evaluation-red?style=for-the-badge"/></a>
    <a href= https://github.com/emre-mr246/42-evaluation><img src="https://img.shields.io/github/last-commit/emre-mr246/42_ring0_libft?style=for-the-badge"/></a>
    <a href="https://42istanbul.com.tr/"><img src="https://img.shields.io/badge/42-ISTANBUL-white?style=for-the-badge"/></a>
   
<h4>
    <a href="https://github.com/emre-mr246/42_ring0_libft/issues">❔ Ask a Question</a>
  <span> · </span>
    <a href="https://github.com/emre-mr246/42_ring0_libft/issues">🪲 Report Bug</a>
  <span> · </span>
    <a href="https://github.com/emre-mr246/42_ring0_libft/issues">💬 Request Feature</a>
</h4>
</div>

## Introduction 🚀

The project aims to promote a thorough comprehension of essential C functions, empowering students to develop their own implementations. Furthermore, libft will be utilized in upcoming Ecole 42 projects.

## Functions in libft 📚

Functions from <ctype.h>

    ft_isalpha: Checks if a character is alphabetic.
    ft_isdigit: Checks if a character is a digit (0-9).
    ft_isalnum: Checks if a character is alphanumeric.
    ft_isascii: Checks if a character is within the ASCII range.
    ft_isprint: Checks if a character is printable.
    ft_toupper: Converts a character to uppercase.
    ft_tolower: Converts a character to lowercase.

Functions from <string.h>

    ft_memset: Fills memory with a specified byte.
    ft_strlen: Calculates the length of a string.
    ft_bzero: Sets a byte string to zero.
    ft_memcpy: Copies memory to another location.
    ft_memmove: Copies memory to another location, handling overlap.
    ft_strlcpy: Copies a string to a specific size.
    ft_strlcat: Concatenates strings up to a specific size.
    ft_strchr: Locates the first occurrence of a character in a string.
    ft_strrchr: Locates the last occurrence of a character in a string.
    ft_strncmp: Compares a specific number of characters in two strings.
    ft_memchr: Locates the first occurrence of a character in memory.
    ft_memcmp: Compares memory byte by byte.
    ft_strnstr: Locates a substring in a string up to a specified length.
    ft_strdup: Duplicates a string.

Functions from <stdlib.h>

    ft_atoi: Converts a string to an integer.
    ft_calloc: Allocates memory for an array and initializes it with zeros.

Non-standard functions

    ft_substr: Extracts a substring from a string.
    ft_strjoin: Concatenates two strings.
    ft_strtrim: Trims leading and trailing whitespace from a string.
    ft_split: Splits a string into an array of substrings based on a delimiter.
    ft_itoa: Converts an integer to a string.
    ft_strmapi: Applies a function to each character of a string.
    ft_striteri: Applies a function to each character of a string with its index.
    ft_putchar_fd: Outputs a character to a specified file descriptor.
    ft_putstr_fd: Outputs a string to a specified file descriptor.
    ft_putendl_fd: Outputs a string followed by a newline to a specified file descriptor.
    ft_putnbr_fd: Outputs an integer to a specified file descriptor.

Linked list functions

    ft_lstnew: Creates a new list node.
    ft_lstadd_front: Adds a node at the beginning of a list.
    ft_lstsize: Counts the number of nodes in a list.
    ft_lstlast: Returns the last node of a list.
    ft_lstadd_back: Adds a node at the end of a list.
    ft_lstdelone: Deletes a single node from a list.
    ft_lstclear: Deletes and frees all nodes in a list.
    ft_lstiter: Applies a function to each node in a list.
    ft_lstmap: Applies a function to each node in a list and creates a new list.

    
## Usage 🔍

1.  In the project's main directory, compile the library using the `make` command.
   `$ make` 

2.  After compilation, include the `libft.h` in your project.
    `#include "libft.h"`
    
3.  Compile your project by including the `libft.a`.
    `$ gcc -o my_program my_program.c -lft`
