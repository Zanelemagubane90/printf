#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @vtypes: List a of arguments
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags
 * @vwidth: get vwidth
 * @vprecision: vprecision specification
 * @vsize: vsize specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list vtypes, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{
	char vextra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, vlength = 2, padd_start = 1; /* vlength=2, for '0x' */
	unsigned long vaddrs;
	char mymap[] = "0123456789abcdef";
	void *addrs = va_arg(vtypes, void *);

	UNUSED(vwidth);
	UNUSED(vsize);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	vbuffer[BUFF_SIZE - 1] = '\0';
	UNUSED(vprecision);

	vaddrs = (unsigned long)addrs;

	while (vaddrs > 0)
	{
		vbuffer[ind--] = mymap[vaddrs % 16];
		vaddrs /= 16;
		vlength++;
	}

	if ((vflags & F_ZERO) && !(vflags & F_MINUS))
		padd = '0';
	if (vflags & F_PLUS)
		vextra_c = '+', vlength++;
	else if (vflags & F_SPACE)
		vextra_c = ' ', vlength++;

	ind++;

	/*return (write(1, &vbuffer[vi], BUFF_SIZE - vi - 1));*/
	return (write_pointer(vbuffer, ind, vlength,
		vwidth, vflags, padd, vextra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @vtypes: Lista of arguments
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags
 * @vwidth: get vwidth
 * @vprecision: vprecision specification
 * @vsize: vsize specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list vtypes, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{
	int mymap = 0, offset = 0;
	char *str = va_arg(vtypes, char *);

	UNUSED(vflags);
	UNUSED(vwidth);
	UNUSED(vprecision);
	UNUSED(vsize);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[mymap] != '\0')
	{
		if (is_printable(str[mymap]))
			vbuffer[mymap + offset] = str[vi];
		else
			offset += append_hexa_code(str[vi], vbuffer, vi + offset);

		vi++;
	}

	vbuffer[vi + offset] = '\0';

	return (write(1, vbuffer, vi + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @vtypes: Lista of arguments
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags
 * @vwidth: get vwidth
 * @vprecision: vprecision specification
 * @vsize: vsize specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list vtypes, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{
	char *str;
	int vi, mycount = 0;

	UNUSED(vbuffer);
	UNUSED(vflags);
	UNUSED(vwidth);
	UNUSED(vsize);

	str = va_arg(vtypes, char *);

	if (str == NULL)
	{
		UNUSED(vprecision);

		str = ")Null(";
	}
	for (vi = 0; str[vi]; vi++)
		;

	for (vi = vi - 1; vi >= 0; vi--)
	{
		char z = str[vi];

		write(1, &z, 1);
		mycount++;
	}
	return (mycount);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13.
 * @vtypes: Lista of arguments
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags
 * @vwidth: get vwidth
 * @vprecision: vprecision specification
 * @vsize: vsize specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list vtypes, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{
	char x;
	char *str;
	unsigned int vi, j;
	int mycount = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(vtypes, char *);
	UNUSED(vbuffer);
	UNUSED(vflags);
	UNUSED(vwidth);
	UNUSED(vprecision);
	UNUSED(vsize);

	if (str == NULL)
		str = "(AHYY)";
	for (vi = 0; str[vi]; vi++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[vi])
			{
				x = out[j];
				write(1, &x, 1);
				mycount++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[vi];
			write(1, &x, 1);
			mycount++;
		}
	}
	return (mycount);
}

