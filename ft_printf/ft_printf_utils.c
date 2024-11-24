#include "ft_printf.h"

// Function to print a single character
int	ft_printchar(int c)
{
    write(1, &c, 1); // Write the character to the standard output
    return (1); // Return the number of characters printed (always 1)
}

// Function to print a string
int	ft_printstr(char *str)
{
    int	count; // Variable to keep track of the number of characters printed

    count = 0; // Initialize count to 0
    if (!str) // Check if the string is NULL
        str = "(null)"; // Use "(null)" as the string if it is NULL
    while (*str) // Loop through each character in the string
    {
        write(1, str, 1); // Write the current character to the standard output
        str++; // Move to the next character
        count++; // Increment the count
    }
    return (count); // Return the total number of characters printed
}

// Function to print an integer
int	ft_printnbr(int n)
{
    char			c;      // Variable to store the current digit as a character
    int				count;  // Variable to keep track of the number of characters printed
    unsigned int	num;    // Variable to store the absolute value of the number

    count = 0; // Initialize count to 0
    if (n == INT_MIN) // Check if the number is the minimum integer value
    {
        write(1, "-2147483648", 11); // Print the minimum integer value directly
        return (11); // Return the number of characters printed
    }
    if (n < 0) // Check if the number is negative
    {
        write(1, "-", 1); // Print the negative sign
        count++; // Increment the count
        num = (unsigned int)(-n); // Convert the number to its absolute value
    }
    else // If the number is non-negative
    {
        num = (unsigned int)n; // Use the number as is
    }
    if (num >= 10) // Check if the number has more than one digit
        count += ft_printnbr(num / 10); // Recursively print the higher order digits
    c = (char)(num % 10 + '0'); // Convert the current digit to a character
    write(1, &c, 1); // Print the current digit
    return (count + 1); // Return the total number of characters printed
}

// Function to print an unsigned integer
int	ft_printnbru(unsigned int n)
{
    int		count; // Variable to keep track of the number of characters printed
    char	c;     // Variable to store the current digit as a character

    count = 0; // Initialize count to 0
    if (n >= 10) // Check if the number has more than one digit
        count += ft_printnbru(n / 10); // Recursively print the higher order digits
    c = (char)(n % 10 + '0'); // Convert the current digit to a character
    write(1, &c, 1); // Print the current digit
    return (count + 1); // Return the total number of characters printed
}

// Function to print a number in hexadecimal format
int	ft_print_hex(unsigned long n, int upper)
{
    int		count; // Variable to keep track of the number of characters printed
    char	c;     // Variable to store the current digit as a character

    count = 0; // Initialize count to 0
    if (n >= 16) // Check if the number has more than one digit in hexadecimal
        count += ft_print_hex(n / 16, upper); // Recursively print the higher order digits
    if (n % 16 < 10) // Check if the current digit is less than 10
        c = "0123456789"[n % 16]; // Convert the digit to a character
    else // If the current digit is 10 or greater
    {
        if (upper) // Check if the hexadecimal should be in uppercase
            c = "ABCDEF"[n % 16 - 10]; // Convert the digit to an uppercase character
        else // If the hexadecimal should be in lowercase
            c = "abcdef"[n % 16 - 10]; // Convert the digit to a lowercase character
    }
    write(1, &c, 1); // Print the current digit
    return (count + 1); // Return the total number of characters printed
}

// Function to print a pointer
int	ft_print_pointer(void *ptr)
{
    int	count; // Variable to keep track of the number of characters printed

    if (ptr == NULL) // Check if the pointer is NULL
    {
        write(1, "(nil)", 5); // Print "(nil)" for NULL pointers
        return (5); // Return the number of characters printed
    }
    count = 0; // Initialize count to 0
    write(1, "0x", 2); // Print the "0x" prefix for hexadecimal pointers
    count += 2; // Increment the count by 2
    count += ft_print_hex((unsigned long)ptr, 0); // Print the pointer value in hexadecimal
    return (count); // Return the total number of characters printed
}