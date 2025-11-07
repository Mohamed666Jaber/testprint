#include "ft_printf.h"

t_flags	ft_init_flags(void)
{
	t_flags	flags;

	flags.minus = 0;
	flags.zero = 0;
	flags.width = 0;
	flags.precision = -1;
	flags.dot = 0;
	flags.hash = 0;
	flags.space = 0;
	flags.plus = 0;
	return (flags);
}

static int	ft_isflag(char c)
{
	return (c == '-' || c == '0' || c == '.' || c == '#' || 
			c == ' ' || c == '+');
}

t_flags	ft_parse_flags(const char *format, int *i, va_list args)
{
	t_flags	flags;

	flags = ft_init_flags();
	while (ft_isflag(format[*i]))
	{
		if (format[*i] == '-')
			flags.minus = 1;
		else if (format[*i] == '0')
			flags.zero = 1;
		else if (format[*i] == '#')
			flags.hash = 1;
		else if (format[*i] == ' ')
			flags.space = 1;
		else if (format[*i] == '+')
			flags.plus = 1;
		else if (format[*i] == '.')
		{
			flags.dot = 1;
			(*i)++;
			if (format[*i] == '*')
				flags.precision = va_arg(args, int);
			else
				flags.precision = ft_atoi(&format[*i]);
			while (ft_isdigit(format[*i]))
				(*i)++;
			continue;
		}
		(*i)++;
	}
	if (format[*i] == '*')
	{
		flags.width = va_arg(args, int);
		(*i)++;
	}
	else if (ft_isdigit(format[*i]))
	{
		flags.width = ft_atoi(&format[*i]);
		while (ft_isdigit(format[*i]))
			(*i)++;
	}
	if (flags.minus)
		flags.zero = 0;
	if (flags.plus)
		flags.space = 0;
	return (flags);
}

int	ft_print_format_bonus(char c, va_list args, t_flags flags)
{
	if (c == 'c')
		return (ft_print_char(va_arg(args, int), flags));
	else if (c == 's')
		return (ft_print_str(va_arg(args, char *), flags));
	else if (c == 'p')
		return (ft_print_ptr(va_arg(args, void *), flags));
	else if (c == 'd' || c == 'i')
		return (ft_print_int(va_arg(args, int), flags));
	else if (c == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int), flags));
	else if (c == 'x' || c == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), c, flags));
	else if (c == '%')
		return (ft_print_percent(flags));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;
	t_flags	flags;

	count = 0;
	i = 0;
	va_start(args, format);
	if (!format)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			flags = ft_parse_flags(format, &i, args);
			count += ft_print_format_bonus(format[i], args, flags);
		}
		else if (format[i] != '%')
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}