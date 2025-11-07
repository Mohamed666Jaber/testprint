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

static int	ft_handle_sign(int n, t_flags *flags)
{
	int	count;

	count = 0;
	if (n < 0)
		count += ft_putchar_len('-');
	else if (flags->plus)
		count += ft_putchar_len('+');
	else if (flags->space)
		count += ft_putchar_len(' ');
	return (count);
}

static int	ft_putnbr_precision(long long n, int precision, int base_len)
{
	int	count;
	int	num_len;
	int	padding;

	count = 0;
	num_len = ft_num_len(n, base_len);
	if (n == 0 && precision == 0)
		return (0);
	padding = precision - num_len;
	while (padding > 0)
	{
		count += ft_putchar_len('0');
		padding--;
	}
	count += ft_putnbr_len(n);
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
	int	i;

	count = 0;
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (flags.dot >= 0 && flags.dot < len)
		len = flags.dot;
	if (flags.minus)
	{
		i = 0;
		while (i < len)
			count += ft_putchar_len(str[i++]);
		count += ft_put_padding(flags.width, len, 0);
	}
	else
	{
		count += ft_put_padding(flags.width, len, flags.zero);
		i = 0;
		while (i < len)
			count += ft_putchar_len(str[i++]);
	}
	return (count);
}

int	ft_handle_pointer(void *p, t_flags flags)
{
	unsigned long	address;
	int				count;
	int				len;
	char			*hex;

	count = 0;
	if (!p)
	{
		if (flags.dot >= 0)
			return (ft_handle_string("0x0", flags));
		else
			return (ft_handle_string("(nil)", flags));
	}
	address = (unsigned long)p;
	hex = "0123456789abcdef";
	len = ft_unum_len(address, 16) + 2; // +2 for "0x"
	if (flags.minus)
	{
		count += ft_putstr_len("0x");
		count += ft_putnbr_base(address, hex);
		count += ft_put_padding(flags.width, len, 0);
	}
	else
	{
		count += ft_put_padding(flags.width, len, flags.zero);
		count += ft_putstr_len("0x");
		count += ft_putnbr_base(address, hex);
	}
	return (count);
}

int	ft_handle_int(int n, t_flags flags)
{
	int		count;
	int		len;
	int		sign_len;
	long	num;

	count = 0;
	num = n;
	if (flags.dot == 0 && num == 0)
		return (ft_put_padding(flags.width, 0, 0));
	sign_len = (n < 0 || flags.plus || flags.space) ? 1 : 0;
	len = ft_num_len(num, 10);
	if (flags.dot > len)
		len = flags.dot;
	if (flags.minus)
	{
		count += ft_handle_sign(n, &flags);
		count += ft_putnbr_precision(num, flags.dot, 10);
		count += ft_put_padding(flags.width, len + sign_len, 0);
	}
	else
	{
		if (flags.zero && flags.dot == -1)
		{
			count += ft_handle_sign(n, &flags);
			count += ft_put_padding(flags.width, len + sign_len, 1);
			count += ft_putnbr_precision(num, flags.dot, 10);
		}
		else
		{
			count += ft_put_padding(flags.width, len + sign_len, 0);
			count += ft_handle_sign(n, &flags);
			count += ft_putnbr_precision(num, flags.dot, 10);
		}
	}
	return (count);
}

int	ft_handle_unsigned(unsigned int n, t_flags flags)
{
	int	count;
	int	len;

	count = 0;
	if (flags.dot == 0 && n == 0)
		return (ft_put_padding(flags.width, 0, 0));
	len = ft_unum_len(n, 10);
	if (flags.dot > len)
		len = flags.dot;
	if (flags.minus)
	{
		count += ft_putunbr_precision(n, flags.dot);
		count += ft_put_padding(flags.width, len, 0);
	}
	else
	{
		if (flags.zero && flags.dot == -1)
		{
			count += ft_put_padding(flags.width, len, 1);
			count += ft_putunbr_precision(n, flags.dot);
		}
		else
		{
			count += ft_put_padding(flags.width, len, 0);
			count += ft_putunbr_precision(n, flags.dot);
		}
	}
	return (count);
}

static int	ft_puthex_precision(unsigned int n, int precision, char *base)
{
	int	count;
	int	num_len;
	int	padding;

	count = 0;
	num_len = ft_unum_len(n, 16);
	if (n == 0 && precision == 0)
		return (0);
	padding = precision - num_len;
	while (padding > 0)
	{
		count += ft_putchar_len('0');
		padding--;
	}
	if (n == 0)
		count += ft_putchar_len('0');
	else
		count += ft_putnbr_base(n, base);
	return (count);
}

int	ft_handle_hex(unsigned int n, int uppercase, t_flags flags)
{
	int		count;
	int		len;
	char	*base;

	count = 0;
	base = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
	if (flags.dot == 0 && n == 0)
		return (ft_put_padding(flags.width, 0, 0));
	len = ft_unum_len(n, 16);
	if (flags.dot > len)
		len = flags.dot;
	if (flags.hash && n != 0)
		len += 2;
	if (flags.minus)
	{
		if (flags.hash && n != 0)
			count += ft_putstr_len(uppercase ? "0X" : "0x");
		count += ft_puthex_precision(n, flags.dot, base);
		count += ft_put_padding(flags.width, len, 0);
	}
	else
	{
		if (flags.zero && flags.dot == -1)
		{
			if (flags.hash && n != 0)
				count += ft_putstr_len(uppercase ? "0X" : "0x");
			count += ft_put_padding(flags.width, len, 1);
			count += ft_puthex_precision(n, flags.dot, base);
		}
		else
		{
			count += ft_put_padding(flags.width, len, 0);
			if (flags.hash && n != 0)
				count += ft_putstr_len(uppercase ? "0X" : "0x");
			count += ft_puthex_precision(n, flags.dot, base);
		}
	}
	return (count);
}

int	ft_handle_percent(t_flags flags)
{
	int	count;

	count = 0;
	if (flags.minus)
	{
		count += ft_putchar_len('%');
		count += ft_put_padding(flags.width, 1, 0);
	}
	else if (flags.zero)
	{
		count += ft_put_padding(flags.width, 1, 1);
		count += ft_putchar_len('%');
	}
	else
	{
		count += ft_put_padding(flags.width, 1, 0);
		count += ft_putchar_len('%');
	}
	return (count);
}