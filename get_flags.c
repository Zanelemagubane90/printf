#include "main.h"

/**
 * get_flags - Calculates active vflags
 * @vformat: Formatted string in which to print the arguments
 * @vi: take a parameter.
 * Return: vflags:
 */
int get_flags(const char *vformat, int *vi)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, curr_i;
	int vflags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_i = *vi + 1; vformat[curr_i] != '\0'; curr_i++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (vformat[curr_i] == FLAGS_CH[j])
			{
				vflags |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*vi = curr_i - 1;

	return (vflags);
}



