#include "main.h"

/**
 * print_char - a function that prints a char
 * @types: List of arguments
 * @buffer: Arrays for  storing the binary representation
 * @flags:  Active formatting flags
 * @width: Width specification for formatting
 * @precision: Precision specification for formatting
 * @size: Size specifier for formatting
 * Return: the number of characters to be printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char chr = va_arg(types, int);

	return (handle_write_char(chr, buffer, flags, width, precision, size));
}


/**
 * print_string - a function that prints a string
 * @types: List of arguments
 * @buffer: Arrays for  storing the binary representation
 * @flags:  Active formatting flags
 * @width: Width specification for formatting
 * @precision: Precision specification for formatting
 * @size: Size specifier for formatting
 * Return: the number of characters to be printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, len = 0;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}

/**
 * print_percent - Prints a percent sign
 * @types: List of arguments
 * @buffer: Arrays for  storing the binary representation
 * @flags:  Active formatting flags
 * @width: Width specification for formatting
 * @precision: Precision specification for formatting
 * @size: Size specifier for formatting
 * Return: the number of characters to be printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - Print int
 * @types: List of arguments
 * @buffer: Arrays for  storing the binary representation
 * @flags:  Active formatting flags
 * @width: Width specification for formatting
 * @precision: Precision specification for formatting
 * @size: Size specifier for formatting
 * Return: the number of characters to be printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int number;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	number = (unsigned long int)n;

	if (n < 0)
	{
		number = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (number > 0)
	{
		buffer[i--] = (number % 10) + '0';
		number /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/**
 * print_binary - Prints an unsigned number
 * @types: List of arguments
 * @buffer: Arrays for  storing the binary representation
 * @flags:  Active formatting flags
 * @width: Width specification for formatting
 * @precision: Precision specification for formatting
 * @size: Size specifier for formatting
 * Return: the number of characters to be printed
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int num, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	num = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = num / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (num / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}


