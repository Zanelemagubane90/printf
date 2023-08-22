#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Prints an unsigned number
 * @vtypes: List a of arguments
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags
 * @vwidth: get vwidth
 * @vprecision: vprecision specification
 * @vsize: vsize specifier
 * Return: Number of chars printed.
 */
int print_unsigned(va_list vtypes, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{
	int vi = BUFF_SIZE - 2;
	unsigned long int mynum = va_arg(vtypes, unsigned long int);

	mynum = convert_size_unsgnd(mynum, vsize);

	if (mynum == 0)
		vbuffer[vi--] = '0';

	vbuffer[BUFF_SIZE - 1] = '\0';

	while (mynum > 0)
	{
		vbuffer[vi--] = (mynum % 10) + '0';
		mynum /= 10;
	}

	vi++;

	return (write_unsgnd(0, vi, vbuffer, vflags, vwidth, vprecision, vsize));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @vtypes: Lista of arguments
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags
 * @vwidth: get vwidth
 * @vprecision: vprecision specification
 * @vsize: vsize specifier
 * Return: Number of chars printed
 */
int print_octal(va_list vtypes, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{

	int vi = BUFF_SIZE - 2;
	unsigned long int mynum = va_arg(vtypes, unsigned long int);
	unsigned long int init_num = mynum;

	UNUSED(vwidth);

	mynum = convert_size_unsgnd(mynum, vsize);

	if (mynum == 0)
		vbuffer[vi--] = '0';

	vbuffer[BUFF_SIZE - 1] = '\0';

	while (mynum > 0)
	{
		vbuffer[vi--] = (mynum % 8) + '0';
		mynum /= 8;
	}

	if (vflags & F_HASH && init_num != 0)
		vbuffer[vi--] = '0';

	vi++;

	return (write_unsgnd(0, vi, vbuffer, vflags, vwidth, vprecision, vsize));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @vtypes: Lista of arguments
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags
 * @vwidth: get vwidth
 * @vprecision: vprecision specification
 * @vsize: vsize specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list vtypes, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{
	return (print_hexa(vtypes, "0123456789abcdef", vbuffer,
		vflags, 'x', vwidth, vprecision, vsize));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @vtypes: Lista of arguments
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags
 * @vwidth: get vwidth
 * @vprecision: vprecision specification
 * @vsize: vsize specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list vtypes, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{
	return (print_hexa(vtypes, "0123456789ABCDEF", vbuffer,
		vflags, 'X', vwidth, vprecision, vsize));
}

/************** PRINT HEXX mynum IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @vtypes: Lista of arguments
 * @map_to: Array of values to map the number to
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags
 * @flag_ch: Calculates active vflags
 * @vwidth: get vwidth
 * @vprecision: vprecision specification
 * @vsize: vsize specifier
 * @vsize: vsize specification
 * Return: Number of chars printed
 */
int print_hexa(va_list vtypes, char map_to[], char vbuffer[],
	int vflags, char flag_ch, int vwidth, int vprecision, int vsize)
{
	int vi = BUFF_SIZE - 2;
	unsigned long int mynum = va_arg(vtypes, unsigned long int);
	unsigned long int init_num = mynum;

	UNUSED(vwidth);

	mynum = convert_size_unsgnd(mynum, vsize);

	if (mynum == 0)
		vbuffer[vi--] = '0';

	vbuffer[BUFF_SIZE - 1] = '\0';

	while (mynum > 0)
	{
		vbuffer[vi--] = map_to[mynum % 16];
		mynum /= 16;
	}

	if (vflags & F_HASH && init_num != 0)
	{
		vbuffer[vi--] = flag_ch;
		vbuffer[vi--] = '0';
	}

	vi++;

	return (write_unsgnd(0, vi, vbuffer, vflags, vwidth, vprecision, vsize));
}


