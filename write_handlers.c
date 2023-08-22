#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @vc: char types.
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags.
 * @vwidth: get vwidth.
 * @vprecision: vprecision specifier
 * @vsize: vsize specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char vc, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{ /* char is stored at left and paddind at vbuffer's right */
	int vi = 0;
	char vpadd = ' ';

	UNUSED(vprecision);
	UNUSED(vsize);

	if (vflags & F_ZERO)
		vpadd = '0';

	vbuffer[vi++] = vc;
	vbuffer[vi] = '\0';

	if (vwidth > 1)
	{
		vbuffer[BUFF_SIZE - 1] = '\0';
		for (vi = 0; vi < vwidth - 1; vi++)
			vbuffer[BUFF_SIZE - vi - 2] = vpadd;

		if (vflags & F_MINUS)
			return (write(1, &vbuffer[0], 1) +
					write(1, &vbuffer[BUFF_SIZE - vi - 1], vwidth - 1));
		else
			return (write(1, &vbuffer[BUFF_SIZE - vi - 1], vwidth - 1) +
					write(1, &vbuffer[0], 1));
	}

	return (write(1, &vbuffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @vind: char types.
 * @vbuffer: vbuffer array to handle print
 * @vflags:  Calculates active vflags
 * @vwidth: get vwidth.
 * @vprecision: vprecision specifier
 * @vsize: vsize specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int vind, char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{
	int vlength = BUFF_SIZE - vind - 1;
	char vpadd = ' ', extra_ch = 0;

	UNUSED(vsize);

	if ((vflags & F_ZERO) && !(vflags & F_MINUS))
		vpadd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (vflags & F_PLUS)
		extra_ch = '+';
	else if (vflags & F_SPACE)
		extra_ch = ' ';

	return (write_num(vind, vbuffer, vflags, vwidth, vprecision,
		vlength, vpadd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @vind: Index at which the number starts on the vbuffer
 * @vbuffer: vbuffer
 * @vflags: vflags
 * @vwidth: vwidth
 * @vprec: vprecision specifier
 * @vlength: Number vlength
 * @vpadd: Pading char
 * @vextra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int vind, char vbuffer[],
	int vflags, int vwidth, int vprec,
	int vlength, char vpadd, char vextra_c)
{
	int vi, padd_start = 1;

	if (vprec == 0 && vind == BUFF_SIZE - 2 && vbuffer[vind] == '0' && vwidth == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (vprec == 0 && vind == BUFF_SIZE - 2 && vbuffer[vind] == '0')
		vbuffer[vind] = vpadd = ' '; /* vwidth is displayed with padding ' ' */
	if (vprec > 0 && vprec < vlength)
		vpadd = ' ';
	while (vprec > vlength)
		vbuffer[--vind] = '0', vlength++;
	if (vextra_c != 0)
		vlength++;
	if (vwidth > vlength)
	{
		for (vi = 1; vi < vwidth - vlength + 1; vi++)
			vbuffer[vi] = vpadd;
		vbuffer[vi] = '\0';
		if (vflags & F_MINUS && vpadd == ' ')/* Asign extra char to left of vbuffer */
		{
			if (vextra_c)
				vbuffer[--vind] = vextra_c;
			return (write(1, &vbuffer[vind], vlength) + write(1, &vbuffer[1], vi - 1));
		}
		else if (!(vflags & F_MINUS) && vpadd == ' ')/* extra char to left of buff */
		{
			if (vextra_c)
				vbuffer[--vind] = vextra_c;
			return (write(1, &vbuffer[1], vi - 1) + write(1, &vbuffer[vind], vlength));
		}
		else if (!(vflags & F_MINUS) && vpadd == '0')/* extra char to left of vpadd */
		{
			if (vextra_c)
				vbuffer[--padd_start] = vextra_c;
			return (write(1, &vbuffer[padd_start], vi - padd_start) +
				write(1, &vbuffer[vind], vlength - (1 - padd_start)));
		}
	}
	if (vextra_c)
		vbuffer[--vind] = vextra_c;
	return (write(1, &vbuffer[vind], vlength));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @vind: Index at which the number starts in the vbuffer
 * @vbuffer: Array of chars
 * @vflags: vflags specifiers
 * @vwidth: vwidth specifier
 * @vprecision: vprecision specifier
 * @vsize: vsize specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int vind,
	char vbuffer[],
	int vflags, int vwidth, int vprecision, int vsize)
{
	/* The number is stored at the bufer's right and starts at position vi */
	int vlength = BUFF_SIZE - vind - 1, vi = 0;
	char vpadd = ' ';

	UNUSED(is_negative);
	UNUSED(vsize);

	if (vprecision == 0 && vind == BUFF_SIZE - 2 && vbuffer[vind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (vprecision > 0 && vprecision < vlength)
		vpadd = ' ';

	while (vprecision > vlength)
	{
		vbuffer[--vind] = '0';
		vlength++;
	}

	if ((vflags & F_ZERO) && !(vflags & F_MINUS))
		vpadd = '0';

	if (vwidth > vlength)
	{
		for (vi = 0; vi < vwidth - vlength; vi++)
			vbuffer[vi] = vpadd;

		vbuffer[vi] = '\0';

		if (vflags & F_MINUS) /* Asign extra char to left of vbuffer [vbuffer>vpadd]*/
		{
			return (write(1, &vbuffer[vind], vlength) + write(1, &vbuffer[0], vi));
		}
		else /* Asign extra char to left of padding [vpadd>vbuffer]*/
		{
			return (write(1, &vbuffer[0], vi) + write(1, &vbuffer[vind], vlength));
		}
	}

	return (write(1, &vbuffer[vind], vlength));
}

/**
 * write_pointer - Write a memory address
 * @vbuffer: Arrays of chars
 * @vind: Index at which the number starts in the vbuffer
 * @vlength: vlength of number
 * @vwidth: Wwidth specifier
 * @vflags: vflags specifier
 * @vpadd: Char representing the padding
 * @vextra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char vbuffer[], int vind, int vlength,
	int vwidth, int vflags, char vpadd, char vextra_c, int padd_start)
{
	int vi;

	if (vwidth > vlength)
	{
		for (vi = 3; vi < vwidth - vlength + 3; vi++)
			vbuffer[vi] = vpadd;
		vbuffer[vi] = '\0';
		if (vflags & F_MINUS && vpadd == ' ')/* Asign extra char to left of vbuffer */
		{
			vbuffer[--vind] = 'x';
			vbuffer[--vind] = '0';
			if (vextra_c)
				vbuffer[--vind] = vextra_c;
			return (write(1, &vbuffer[vind], vlength) + write(1, &vbuffer[3], vi - 3));
		}
		else if (!(vflags & F_MINUS) && vpadd == ' ')/* extra char to left of vbuffer */
		{
			vbuffer[--vind] = 'x';
			vbuffer[--vind] = '0';
			if (vextra_c)
				vbuffer[--vind] = vextra_c;
			return (write(1, &vbuffer[3], vi - 3) + write(1, &vbuffer[vind], vlength));
		}
		else if (!(vflags & F_MINUS) && vpadd == '0')/* extra char to left of vpadd */
		{
			if (vextra_c)
				vbuffer[--padd_start] = vextra_c;
			vbuffer[1] = '0';
			vbuffer[2] = 'x';
			return (write(1, &vbuffer[padd_start], vi - padd_start) +
				write(1, &vbuffer[vind], vlength - (1 - padd_start) - 2));
		}
	}
	vbuffer[--vind] = 'x';
	vbuffer[--vind] = '0';
	if (vextra_c)
		vbuffer[--vind] = vextra_c;
	return (write(1, &vbuffer[vind], BUFF_SIZE - vind - 1));
}



