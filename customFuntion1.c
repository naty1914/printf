#include "main.h"

/**
 * print_unsigned - it prints an unsigned number
 * @types: List of arguments
 * @buffer: Arrays for  storing the binary representation
 * @flags:  Active formatting flags
 * @width: Width specification for formatting
 * @precision: Precision specification for formatting
 * @size: Size specifier for formatting
 * Return: characters to be printed
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[i--] = (number % 10) + '0';
		number /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}


/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: List of arguments
 * @buffer: Arrays for  storing the binary representation
 * @flags:  Active formatting flags
 * @width: Width specification for formatting
 * @size: Size specifier for formatting
 * @precision: Precision specification for formatting
 * Return: characters to be printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int init_num = number;

	UNUSED(width);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[i--] = (number % 8) + '0';
		number /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}


/**
 * print_hexadecimal - it Prints an unsigned number in hexadecimal notation
 * @types: List of arguments
 * @buffer: Arrays for  storing the binary representation
 * @flags:  Active formatting flags
 * @width: Width specification for formatting
 * @precision: Precision specification for formatting
 * @size: Size specifier for formatting
 * Return: characters to be printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - prints an unsigned number in upper hexadecimal notation
 * @types: List of arguments
 * @buffer: Arrays for  storing the binary representation
 * @flags:  Active formatting flags
 * @width: Width specification for formatting
 * @precision: Precision specification for formatting
 * @size: Size specifier for formatting
 * Return: characters to be printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * print_hexa - prints a hexadecimal number in lower or upper
 * @types: List of arguments
 * @map_to: Array of values to map the number to
 * @flags:  Active formatting flags
 * @flag_ch: Calculates active flags
 * @buffer: Arrays for  storing the binary representation
 * @width: Width specification for formatting
 * @precision: Precision specification for formatting
 * @size: Size specifier for formatting
 * Return: the number of characters to be printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int init_num = number;

	UNUSED(width);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[i--] = map_to[number % 16];
		number /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}


