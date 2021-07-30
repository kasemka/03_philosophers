#include "philo.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	nums[11];
	int		i;
	int		num;

	i = 0;
	num = n;
	if (n == 0)
		write(fd, "0", 1);
	while (num != 0)
	{
		if (num > 0)
			nums[i] = (num % 10) + 48;
		else
			nums[i] = -(num % 10) + 48;
		i++;
		num = num / 10;
	}
	if (n < 0)
		write(fd, "-", 1);
	i--;
	while (i >= 0)
	{
		write(fd, &nums[i], 1);
		i--;
	}
}
