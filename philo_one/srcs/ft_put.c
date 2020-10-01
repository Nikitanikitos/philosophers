
#include "../philo_one.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	const int	buff = ft_strlen(s);

	if (buff)
		write(fd, &(*s), buff);
	write(fd, "\n", 1);
}

void	ft_putnbr_fd(unsigned long nbr, int fd)
{
	char		c;

	if (nbr > 9)
		ft_putnbr_fd(nbr / 10, fd);
	c = nbr % 10 + '0';
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
