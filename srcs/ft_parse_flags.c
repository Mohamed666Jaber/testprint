#include "ft_printf.h"

t_flags	ft_init_flags(void)
{
	t_flags	flags;

	flags.minus = 0;
	flags.zero = 0;
	flags.dot = -1;
	flags.star = 0;
	flags.width = 0;
	flags.precision = -1;
	flags.hash = 0;
	flags.space = 0;
	flags.plus = 0;
	return (flags);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_handle_width_precision(const char *format, int i, 
									t_flags *flags, va_list args)
{
	if (format[i] == '*')
	{
		flags->width = va_arg(args, int);
		if (flags->width < 0)
		{
			flags->minus = 1;
			flags->width = -flags->width;
		}
		i++;
	}
	else
	{
		flags->width = 0;
		while (ft_isdigit(format[i]))
			flags->width = flags->width * 10 + (format[i++] - '0');
	}
	return (i);
}

static int	ft_handle_precision(const char *format, int i, 
							  t_flags *flags, va_list args)
{
	i++;
	if (format[i] == '*')
	{
		flags->precision = va_arg(args, int);
		i++;
	}
	else
	{
		flags->precision = 0;
		while (ft_isdigit(format[i]))
			flags->precision = flags->precision * 10 + (format[i++] - '0');
	}
	return (i);
}

int	ft_parse_flags(const char *format, int i, t_flags *flags, va_list args)
{
	while (format[i])
	{
		if (format[i] == '-')
			flags->minus = 1;
		else if (format[i] == '0' && flags->width == 0 && flags->precision == -1)
			flags->zero = 1;
		else if (format[i] == '.')
			i = ft_handle_precision(format, i, flags, args) - 1;
		else if (format[i] == '*')
			i = ft_handle_width_precision(format, i, flags, args) - 1;
		else if (format[i] == '#')
			flags->hash = 1;
		else if (format[i] == ' ')
			flags->space = 1;
		else if (format[i] == '+')
			flags->plus = 1;
		else if (ft_isdigit(format[i]))
			i = ft_handle_width_precision(format, i, flags, args) - 1;
		else
			break ;
		i++;
	}
	return (i);
}