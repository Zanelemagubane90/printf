#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a char
 * @vtypes: List a of arguments
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags
 * @vwidth: vwidth
 * @vprecision: vprecision specification
 * @vsize: vsize specifier
 * Return: Number of chars printed
 */
int print_char(va_list vtypes, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{
	char c = va_arg(vtypes, int);

	return (handle_write_char(c, vbuffer, vflags, vwidth, vprecision, vsize));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @vtypes: List a of arguments
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags
 * @vwidth: get vwidth.
 * @vprecision: vprecision specification
 * @vsize: vsize specifier
 * Return: Number of chars printed
 */
int print_string(va_list vtypes, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{
	int length = 0, i;
	char *str = va_arg(vtypes, char *);

	UNUSED(vbuffer);
	UNUSED(vflags);
	UNUSED(vwidth);
	UNUSED(vprecision);
	UNUSED(vsize);
	if (str == NULL)
	{
		str = "(null)";
		if (vprecision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (vprecision >= 0 && vprecision < length)
		length = vprecision;

	if (vwidth > length)
	{
		if (vflags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = vwidth - length; i > 0; i--)
				write(1, " ", 1);
			return (vwidth);
		}
		else
		{
			for (i = vwidth - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (vwidth);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @vtypes: Lista of arguments
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags
 * @vwidth: get vwidth.
 * @vprecision: vprecision spec
 * @vsize: vsize specifier
 * Return: Number of chars printed
 */
int print_percent(va_list vtypes, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{
	UNUSED(vtypes);
	UNUSED(vbuffer);
	UNUSED(vflags);
	UNUSED(vwidth);
	UNUSED(vprecision);
	UNUSED(vsize);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print int
 * @vtypes: Lista of arguments
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags
 * @vwidth: get vwidth.
 * @vprecision: vprecision specification
 * @vsize: vsize specifier
 * Return: Number of chars printed
 */
int print_int(va_list vtypes, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(vtypes, long int);
	unsigned long int num;

	n = convert_size_number(n, vsize);

	if (n == 0)
		vbuffer[i--] = '0';

	vbuffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		vbuffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, vbuffer, vflags, vwidth, vprecision, vsize));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @vtypes: Lista of arguments
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags
 * @vwidth: get vwidth.
 * @vprecision: vprecision specification
 * @vsize: vsize specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list vtypes, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(vbuffer);
	UNUSED(vflags);
	UNUSED(vwidth);
	UNUSED(vprecision);
	UNUSED(vsize);

	n = va_arg(vtypes, unsigned int);
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

