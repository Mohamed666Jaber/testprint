#include "ft_printf.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	ft_putchar_count(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_count(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnstr(char *str, int n)
{
	int	i;

	i = 0;
	while (i < n && str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_print_width(int width, int zero)
{
	int	count;

	count = 0;
	while (width > 0)
	{
		if (zero)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		count++;
		width--;
	}
	return (count);
}

int	ft_numlen(long long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_hexlen(unsigned long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}