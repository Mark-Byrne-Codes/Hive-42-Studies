#ifndef FT_PRINTF_H // Include guard to prevent multiple inclusions
# define FT_PRINTF_H

# include <stdarg.h> // Include for handling variable arguments
# include <unistd.h> // Include for write function
# include <stdlib.h> // Include for standard library functions
# include <limits.h> // Include for limits of integer types

// Function prototypes for the ft_printf implementation
int	ft_printf(const char *format, ...); // Main printf function
int	parse_format(const char **format, va_list args); // Function to parse format specifiers
int	ft_printchar(int c); // Function to print a single character
int	ft_printstr(char *str); // Function to print a string
int	ft_printnbr(int n); // Function to print an integer
int	ft_printnbru(unsigned int n); // Function to print an unsigned integer
int	ft_print_hex(unsigned long n, int upper); // Function to print a number in hexadecimal format
int	ft_print_pointer(void *ptr); // Function to print a pointer

#endif // End of include guard