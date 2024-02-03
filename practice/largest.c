#include <limits.h>
#include <stdint.h>
#include <stdio.h>

int main()
{
	int	num_int = (int)9223372036854775807;
	long	num_long = (long)9223372036854775807;
	long long	num_long_long = (long long)9223372036854775807;

	printf("LONG_MAX is %ld\n", LONG_MAX);
	printf("LONG_MAX stored in an `int` is %d\n", num_int);
	printf("LONG_MAX stored in a `long` is %ld\n", num_long);
	printf("LONG_MAX stored in a `long long` is %lld\n", num_long_long);

	printf("sizeof(int) is %zu\n", sizeof(int));
	printf("sizeof(long) is %zu\n", sizeof(long));
	printf("sizeof(long long) is %zu\n", sizeof(long long));
}
