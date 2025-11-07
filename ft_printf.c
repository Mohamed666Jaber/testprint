#include "ft_printf.h"

static int	ft_print_format(char c, t_flags flags, va_list args)
{
	if (c == 'c')
		return (ft_handle_char(va_arg(args, int), flags));
	else if (c == 's')
		return (ft_handle_string(va_arg(args, char *), flags));
	else if (c == 'p')
		return (ft_handle_pointer(va_arg(args, void *), flags));
	else if (c == 'd' || c == 'i')
		return (ft_handle_int(va_arg(args, int), flags));
	else if (c == 'u')
		return (ft_handle_unsigned(va_arg(args, unsigned int), flags));
	else if (c == 'x')
		return (ft_handle_hex(va_arg(args, unsigned int), 0, flags));
	else if (c == 'X')
		return (ft_handle_hex(va_arg(args, unsigned int), 1, flags));
	else if (c == '%')
		return (ft_handle_percent(flags));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;
	t_flags	flags;

	count = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			flags = ft_init_flags();
			i = ft_parse_flags(format, i, &flags, args);
			count += ft_print_format(format[i], flags, args);
		}
		else
			count += ft_putchar_len(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}