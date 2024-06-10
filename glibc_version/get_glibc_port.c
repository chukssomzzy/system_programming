# include <stdio.h>
# include <unistd.h>

/**
 * main - get version information for glibc
 * Return: 0 success
 */
int main(void)
{
#ifndef _CS_GNU_LIBC_VERSION
	printf("Not supported\n");
#else
	char v[20];

	confstr(_CS_GNU_LIBC_VERSION, v, sizeof(v));
	printf("glibc version %s\n", v);
#endif
	return (0);
}
