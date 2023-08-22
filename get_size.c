#include "main.h"

/**
 * get_size - Calculates the vsz to cast the argument
 * @vformat: Formatted string in which to print the arguments
 * @vi: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *vformat, int *vi)
{
	int v_turr = *vi + 1;
	int vsz = 0;

	if (vformat[v_turr] == 'l')
		vsz = S_LONG;
	else if (vformat[v_turr] == 'h')
		vsz = S_SHORT;

	if (vsz == 0)
		*vi = v_turr - 1;
	else
		*vi = v_turr;

	return (vsz);
}


