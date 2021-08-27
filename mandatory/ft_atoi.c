#include "philo.h"

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned long	num;
	unsigned long	len;

	sign = 1;
	num = 0;
	len = 9223372036854775807;
	while (*str == ' ' || *str == '\n' || *str == '\t'
		|| *str == '\v' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (num >= len && sign == 1)
			return (-1);
		else if (num > len && sign == -1)
			return (0);
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num * sign);
}
