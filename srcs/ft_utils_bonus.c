#include "ft_printf.h"

int	ft_putchar_len(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_len(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		ft_putchar_len(str[i++]);
	return (i);
}

int	ft_num_len(long long n, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

int	ft_unum_len(unsigned long long n, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

static int	ft_putnbr_recursive(long long n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_putnbr_recursive(n / 10);
	ft_putchar_len((n % 10) + '0');
	return (count + 1);
}

int	ft_putnbr_len(long long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		ft_putchar_len('-');
		count++;
		n = -n;
	}
	count += ft_putnbr_recursive(n);
	return (count);
}

static int	ft_putunbr_recursive(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_putunbr_recursive(n / 10);
	ft_putchar_len((n % 10) + '0');
	return (count + 1);
}

int	ft_putunbr_len(unsigned int n)
{
	return (ft_putunbr_recursive(n));
}
// Add these functions to your existing ft_utils.c

static int	ft_putunbr_recursive_precision(unsigned int n, int *count)
{
	int	total;

	total = 0;
	if (n >= 10)
		total += ft_putunbr_recursive_precision(n / 10, count);
	if (*count > 0)
	{
		ft_putchar_len((n % 10) + '0');
		total++;
		(*count)--;
	}
	return (total);
}

int	ft_putunbr_precision(unsigned int n, int precision)
{
	int	count;
	int	num_len;

	count = 0;
	num_len = ft_unum_len(n, 10);
	if (n == 0 && precision == 0)
		return (0);
	if (precision > num_len)
	{
		while (precision-- > num_len)
			count += ft_putchar_len('0');
	}
	count += ft_putunbr_len(n);
	return (count);
}

// Update your existing ft_putnbr_base to work with the new system
