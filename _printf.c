#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @my_format: my_format.
 * Return: Printed chars.
 */
int _printf(const char *my_format, ...)
{
	int v, printed = 0, p_chars = 0;
	int aflags, awidth, precision, vsize, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (my_format == NULL)
		return (-1);

	va_start(list, my_format);

	for (v = 0; my_format && my_format[v] != '\0'; v++)
	{
		if (my_format[v] != '%')
		{
			buffer[buff_ind++] = my_format[v];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &my_format[v], 1);*/
			p_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			aflags = get_flags(my_format, &v);
			awidth = get_width(my_format, &v, list);
			precision = get_precision(my_format, &v, list);
			vsize = get_size(my_format, &v);
			++v;
			printed = handle_print(my_format, &v, list, buffer,
				aflags, awidth, precision, vsize);
			if (printed == -1)
				return (-1);
			p_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (p_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}


