#include "main.h"
/**
 * handle_print - Prints an argument based on its type
 * @vfmt: Formatted string in which to print the arguments.
 * @vlist: vlist of arguments to be printed.
 * @vind: vind.
 * @vbuffer: vbuffer array to handle print.
 * @vflags: Calculates active vflags
 * @vwidth: get vwidth.
 * @vprecision: vprecision specification
 * @vsize: vsize specifier
 * Return: 1 or 2;
 */
int handle_print(const char *vfmt, int *vind, va_list vlist, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{
	int i, len_unknown = 0, p_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].vfmt != '\0'; i++)
		if (vfmt[*vind] == fmt_types[i].vfmt)
			return (fmt_types[i].fn(vlist, vbuffer, vflags, vwidth, vprecision, vsize));

	if (fmt_types[i].vfmt == '\0')
	{
		if (vfmt[*vind] == '\0')
			return (-1);
		len_unknown += write(1, "%%", 1);
		if (vfmt[*vind - 1] == ' ')
			len_unknown += write(1, " ", 1);
		else if (vwidth)
		{
			--(*vind);
			while (vfmt[*vind] != ' ' && vfmt[*vind] != '%')
				--(*vind);
			if (vfmt[*vind] == ' ')
				--(*vind);
			return (1);
		}
		len_unknown += write(1, &vfmt[*vind], 1);
		return (len_unknown);
	}
	return (p_chars);
}


