#include "main.h"

/**
 * get_flags - calculate active formatting flags from the format string
 * @format: The formatted string in which to identify flags
 * @i: Pointer to an integer
 * Return:An integer representing the active flags
 */
int get_flags(const char *format, int *i)
{
	int index, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (index = 0; FLAGS_CH[index] != '\0'; index++)
			if (format[curr_i] == FLAGS_CH[index])
			{
				flags |= FLAGS_ARR[index];
				break;
			}

		if (FLAGS_CH[index] == 0)
			break;
	}

	*i = curr_i - 1;

	return (flags);
}
