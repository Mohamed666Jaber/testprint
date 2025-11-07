#include "ft_printf.h"

static int	ft_put_padding(int width, int len, int zero)
{
	int	count;
	int	padding;

	count = 0;
	padding = width - len;
	while (padding > 0)
	{
		if (zero)
			ft_putchar_len('0');
		else
			ft_putchar_len(' ');
		count++;
		padding--;
	}
	return (count);
}

int	ft_handle_char(char c, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.minus)
	{
		count += ft_putchar_len(c);
		count += ft_put_padding(flags.width, 1, 0);
	}
	else
	{
		count += ft_put_padding(flags.width, 1, flags.zero);
		count += ft_putchar_len(c);
	}
	return (count);
}

int	ft_handle_string(char *str, t_flags flags)
{
	int	count;
	int	len;

	count = 0;
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (flags.dot >= 0 && flags.dot < len)
		len = flags.dot;
	if (flags.minus)
	{
		count += ft_putstr_len(str);
		count += ft_put_padding(flags.width, len, 0);
	}
	else
	{
		count += ft_put_padding(flags.width, len, flags.zero);
		count += ft_putstr_len(str);
	}
	return (count);
}

// Add similar handlers for other conversions (int, unsigned, hex, pointer, percent)
// These would be quite extensive, so I'll show the pattern with char and string