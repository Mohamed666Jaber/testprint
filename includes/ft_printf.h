#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_flags
{
	int	minus;
	int	zero;
	int	dot;
	int	star;
	int	width;
	int	precision;
	int	hash;
	int	space;
	int	plus;
}	t_flags;

int		ft_print_memory(void *p);
int		ft_putchar(char c);
int		ft_putnbr_base(long long nbr, char *base);
int		ft_putstr(char *str);
int		ft_strlen(char *str);
int		ft_printf(const char *format, ...);
int		ft_putunbr(unsigned int nbr);
int		ft_isdigit(int c);
t_flags	ft_init_flags(void);
int		ft_parse_flags(const char *format, int i, t_flags *flags, va_list args);
int		ft_handle_char(char c, t_flags flags);
int		ft_handle_string(char *str, t_flags flags);
int		ft_handle_pointer(void *p, t_flags flags);
int		ft_handle_int(int n, t_flags flags);
int		ft_handle_unsigned(unsigned int n, t_flags flags);
int		ft_handle_hex(unsigned int n, int uppercase, t_flags flags);
int		ft_handle_percent(t_flags flags);
int		ft_putchar_len(char c);
int		ft_putstr_len(char *str);
int		ft_putnbr_len(long long n);
int		ft_putunbr_len(unsigned int n);
char	*ft_uitoa(unsigned int n);
int		ft_num_len(long long n, int base);
int		ft_unum_len(unsigned long long n, int base);

#endif