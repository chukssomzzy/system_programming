# include <stdio.h>

/**
 * main - start of exec
 * Return: 0
 */
int main(void)
{
#ifndef __GLIBC__
	printf("not compatible\n");
#else
	printf("Glibc version : %i.%i\n", __GLIBC__, __GLIBC_MINOR__);
#endif
	return (0);
}
