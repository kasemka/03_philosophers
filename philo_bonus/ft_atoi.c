#include "philo_bonus.h"

// short for norm: cond for '\v' || *s == '\r' || *s == '\f' were removed
int	ft_atoi(const char *s)
{
	int				sign;
	unsigned long	num;
	unsigned long	len;

	if (!s)
		return (0);
	sign = 1;
	num = 0;
	len = 9223372036854775807;
	while (*s == ' ' || *s == '\n' || *s == '\t' || *s == '\v')
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		if (num >= len && sign == 1)
			return (-1);
		else if (num > len && sign == -1)
			return (0);
		num = num * 10 + (*s - '0');
		s++;
	}
	return (num * sign);
}
