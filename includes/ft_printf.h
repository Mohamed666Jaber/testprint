#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_flags
{
	int		minus;
	int		zero;
	int		width;
	int		precision;
	int		dot;
	int		hash;
	int		space;
	int		plus;
}	t_flags;

int		ft_print_memory(void *p);
int		ft_putchar(char c);
int		ft_putnbr_base(long long nbr, char *base);
int		ft_putstr(char *str);
int		ft_strlen(char *str);
int		ft_printf(const char *format, ...);
int		ft_putunbr(unsigned int nbr);

/* Bonus functions */
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
t_flags	ft_init_flags(void);
t_flags	ft_parse_flags(const char *format, int *i, va_list args);
int		ft_print_format_bonus(char c, va_list args, t_flags flags);

/* Format handlers with flags */
int		ft_print_char(char c, t_flags flags);
int		ft_print_str(char *str, t_flags flags);
int		ft_print_ptr(void *ptr, t_flags flags);
int		ft_print_int(int n, t_flags flags);
int		ft_print_unsigned(unsigned int n, t_flags flags);
int		ft_print_hex(unsigned int n, char format, t_flags flags);
int		ft_print_percent(t_flags flags);

/* Helper functions */
int		ft_putchar_count(char c);
int		ft_putstr_count(char *str);
int		ft_putnstr(char *str, int n);
int		ft_print_width(int width, int zero);
int		ft_numlen(long long n);
int		ft_hexlen(unsigned long n);

#endif