# include <stdio.h>

# ifdef __GLIBC__
# include <gnu/libc-version.h>
# endif

/**
 * main - print gnu lib c version
 * Return: 0 (success)
 */
int main(void)
{
#ifdef __GLIBC__
	printf("Glibc version %s \n", gnu_get_libc_version());
#endif
	return (0);
}
