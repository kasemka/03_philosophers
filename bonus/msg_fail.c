#include "philo_bonus.h"

int	invalid_input(void)
{
	write(1, "invalid input\n", 14);
	return (1);
}

int	malloc_fail(void)
{
	write(1, "malloc fail\n", 12);
	return (1);
}

//int	mutex_destroy_fail(void)
//{
//	write(1, "mutex destroy fail\n", 19);
//	return (1);
//}
//
//int	pthread_join_fail(void)
//{
//	write(1, "pthread join fail\n", 18);
//	return (1);
//}
//
//int	pthread_create_fail(void)
//{
//	write(1, "pthread create fail\n", 20);
//	return (1);
//}
