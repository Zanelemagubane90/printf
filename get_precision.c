#include "main.h"

/**
 * get_precision - Calculates the pcn for printing
 * @vformat: Formatted string in which to print the arguments
 * @vi: vlist of arguments to be printed.
 * @vlist: vlist of arguments.
 *
 * Return: pcn.
 */
int get_precision(const char *vformat, int *vi, va_list vlist)
{
	int v_turr = *vi + 1;
	int pcn = -1;

	if (vformat[v_turr] != '.')
		return (pcn);

	pcn = 0;

	for (v_turr += 1; vformat[v_turr] != '\0'; v_turr++)
	{
		if (is_digit(vformat[v_turr]))
		{
			pcn *= 10;
			pcn += vformat[v_turr] - '0';
		}
		else if (vformat[v_turr] == '*')
		{
			v_turr++;
			pcn = va_arg(vlist, int);
			break;
		}
		else
			break;
	}

	*vi = v_turr - 1;

	return (pcn);
}

