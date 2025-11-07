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