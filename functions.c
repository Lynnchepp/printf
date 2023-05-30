#include "main.h"

/**
 * print_char - prints a character
 * @types: list of arguments
 * @buffer: buffer array to handle print
 * @flags:  calculates active flags
 * @width: width
 * @size: size specifier
 * @precision: precision specification
 * Return: number of chars printed
 */
int print_char(va_list types, char buffer[],
		int flags, int width, int size, int precision)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, size,
				precision));
}
/**
 * print_string - prints string
 * @types: list of arguments
 * @buffer: buffer array to handle print
 * @flags: calculates active flags
 * @width: gets the width
 * @size: size specifier
 * @precision: precision specification
 * Return: number of chars printed
 */
int print_string(va_list types, char buffer[],
		int flags, int width, int size, int precision)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	UNUSED(precision);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "     ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}
/**
 * print_percent - prints percent sign
 * @buffer: buffer array to handle print
 * @types: list of auguments
 * @flags: calculates active flags
 * @width: width
 * @size: size specifier
 * @precision: precision specificatins
 * Return: number of char printed
 */
int print_percent(va_list types, char buffer[], int flags,
		int width, int size, int precision)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	UNUSED(precision);
	return (write(1, "%%", 1));
}
/**
 * print_int - prints int
 * @types: list of urguments
 * @buffer: buffer array to handle print
 * @flags: calculates flags
 * @width: width
 * @size: size specifier
 * @precision: precision specification
 * Return: number of chars printed
 */
int print_int(va_list types, char buffer[], int flags,
		int width, int size, int precision)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;
	return (write_number(is_negative, i, buffer, flags, width,
				size, precision));
}

/**
 * print_binary - prints an unsigned number
 * @types: list of arguments
 * @flags: calculates active flags
 * @buffer: buffer array to handle print
 * @width: width
 * @size: size specifier
 * @precision: precision specification
 * Return: number of chars printed
 */
int print_binary(va_list types, char buffer[], int flags,
int width, int size, int precision)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	UNUSED(precision);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
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
