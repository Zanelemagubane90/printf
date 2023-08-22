#include "main.h"

/**
 * is_printable - Evaluates if a char is printable
 * @cc: Char to be evaluated.
 *
 * Return: 1 if cc is printable, 0 otherwise
 */
int is_printable(char cc)
{
	if (cc >= 32 && cc < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascci in hexadecimal code to vbuffer
 * @vbuffer: Array of chars.
 * @vi: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char vbuffer[], int vi)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	vbuffer[vi++] = '\\';
	vbuffer[vi++] = 'x';

	vbuffer[vi++] = map_to[ascii_code / 16];
	vbuffer[vi] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies if a char is a digit
 * @cc: Char to be evaluated
 *
 * Return: 1 if cc is a digit, 0 otherwise
 */
int is_digit(char cc)
{
	if (cc >= '0' && cc <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a number to the specified vsize
 * @mynum: Number to be casted.
 * @vsize: Number indicating the type to be casted.
 *
 * Return: Casted value of mynum
 */
long int convert_size_number(long int mynum, int vsize)
{
	if (vsize == S_LONG)
		return (mynum);
	else if (vsize == S_SHORT)
		return ((short)mynum);

	return ((int)mynum);
}

/**
 * convert_size_unsgnd - Casts a number to the specified vsize
 * @mynum: Number to be casted
 * @vsize: Number indicating the type to be casted
 *
 * Return: Casted value of mynum
 */
long int convert_size_unsgnd(unsigned long int mynum, int vsize)
{
	if (vsize == S_LONG)
		return (mynum);
	else if (vsize == S_SHORT)
		return ((unsigned short)mynum);

	return ((unsigned int)mynum);
}

