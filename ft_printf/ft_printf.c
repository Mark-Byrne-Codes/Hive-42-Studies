#include "ft_printf.h"

// Function to parse the format specifier and call the appropriate print function
int	parse_format(const char **format, va_list args)
{
    int	count; // Variable to keep track of the number of characters printed

    count = 0; // Initialize count to 0
    if (**format == 'c') // If the format specifier is 'c'
        count += ft_printchar(va_arg(args, int)); // Print a character
    else if (**format == 's') // If the format specifier is 's'
        count += ft_printstr(va_arg(args, char *)); // Print a string
    else if (**format == 'd' || **format == 'i') // If the format specifier is 'd' or 'i'
        count += ft_printnbr(va_arg(args, int)); // Print an integer
    else if (**format == 'u') // If the format specifier is 'u'
        count += ft_printnbru(va_arg(args, unsigned int)); // Print an unsigned integer
    else if (**format == 'x') // If the format specifier is 'x'
        count += ft_print_hex(va_arg(args, unsigned int), 0); // Print a hexadecimal number (lowercase)
    else if (**format == 'X') // If the format specifier is 'X'
        count += ft_print_hex(va_arg(args, unsigned int), 1); // Print a hexadecimal number (uppercase)
    else if (**format == 'p') // If the format specifier is 'p'
        count += ft_print_pointer(va_arg(args, void *)); // Print a pointer
    else if (**format == '%') // If the format specifier is '%'
        count += ft_printchar('%'); // Print a percent sign
    else // If the format specifier is invalid
    {
        ft_printstr("Error: Invalid format specifier\n"); // Print an error message
        return (-1); // Return -1 to indicate an error
    }
    return (count); // Return the number of characters printed
}

// Function to implement the printf functionality
int	ft_printf(const char *format, ...)
{
    int		count; // Variable to keep track of the number of characters printed
    va_list	args; // Variable to hold the list of arguments
    int		error; // Variable to check for errors

    va_start(args, format); // Initialize the argument list
    count = 0; // Initialize count to 0
    while (*format) // Loop through the format string
    {
        if (*format == '%') // If the current character is '%'
        {
            format++; // Move to the next character
            error = parse_format(&format, args); // Parse the format specifier and print the corresponding value
            if (error == -1) // If there was an error
            {
                va_end(args); // Clean up the argument list
                return (-1); // Return -1 to indicate an error
            }
            count += error; // Add the number of characters printed to the count
        }
        else // If the current character is not '%'
            count += ft_printchar(*format); // Print the character
        format++; // Move to the next character
    }
    va_end(args); // Clean up the argument list
    return (count); // Return the total number of characters printed
}