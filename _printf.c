#include "main.h"

void cleanup(va_list args, buffer_t *output);
int run_printf(const char *format, va_list args, buffer_t *output);
int _printf(const char *format, ...);

/**
 * cleanup - Peforms cleanup operations for the method.
 * @args: A va_list of arguments.
 * @output: A buffer_t struct.
 */

void cleanup(va_list args, buffer_t *output)
{

	va_end(args);
	write(1, output->start, output->len);
	free_buffer(output);
}

/**
 * run_printf - Checks through the format string for _printf.
 * @format: Character string to print .
 * @output: A buffer_t struct containing a buffer.
 * @args: A va_list of arguments.
 * Return: Number of characters stored to output.
 */

int run_printf(const char *format, va_list args, buffer_t *output)
{


unsigned int (*f)(va_list, buffer_t *, unsigned char, int, int, unsigned char);
	unsigned char len, flags;

	int  prec, i, wid,  retvalue = 0;
	char temp;

	for (i = 0; *(format + i); i++)
	{
		len = 0;

		if (*(format + i) == '%')

		{
			temp = 0;
			flags = handle_flags(format + i + 1, &temp);
			wid = handle_width(args, format + i + temp + 1, &temp);
			prec = handle_precision(args, format + i + temp + 1, &temp);
			len = handle_length(format + i + temp + 1, &temp);
			f = handle_specifiers(format + i + temp + 1);

			if (f != NULL)
			{
				i += temp + 1;
				retvalue += f(args, output, flags, wid, prec, len);
				continue;
			}
			else if (*(format + i + temp + 1) == '\0')
			{
				retvalue = -1;
				break;
			}
		}
		retvalue += _memcpy(output, (format + i), 1);
		i += (len != 0) ? 1 : 0;

	}
	cleanup(args, output);
	return (retvalue);

}


/**
 * _printf - Outputs a formatted string.
 * @format: Character string to print - may contain directives.
 *
 * Return: The number of characters printed.
 */


int _printf(const char *format, ...)
{

	buffer_t *output;
	int retvalue;
	va_list args;

	if (format == NULL)
	return (-1);
	output = init_buffer();

	if (output == NULL)
	return (-1);

	va_start(args, format);
	retvalue = run_printf(format, args, output);
	return (retvalue);
}
