#include "main.h"

/**
 * get_width - Calculates the vwidth for printing
 * @vformat: Formatted string in which to print the arguments.
 * @vi: vlist of arguments to be printed.
 * @vlist: vlist of arguments.
 *
 * Return: vwidth.
 */
int get_width(const char *vformat, int *vi, va_list vlist)
{
	int v_turr;
	int vwidth = 0;

	for (v_turr = *vi + 1; vformat[v_turr] != '\0'; v_turr++)
	{
		if (is_digit(vformat[v_turr]))
		{
			vwidth *= 10;
			vwidth += vformat[v_turr] - '0';
		}
		else if (vformat[v_turr] == '*')
		{
			v_turr++;
			vwidth = va_arg(vlist, int);
			break;
		}
		else
			break;
	}

	*vi = v_turr - 1;

	return (vwidth);
}

