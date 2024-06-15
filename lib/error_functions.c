# include <stdarg.h>
# include "tlpi_hdr.h"
# include "ename.c.inc"
static void terminate(Boolean useExit3);

# ifndef __GNUC__
# define __attribute__ ((__noreturn__))
# endif

/**
 * terminate - terminate a function with exit(3) or _exit()
 *		depending on arg
 * @useExit3: boolean value for the exit function to use
 */
void terminate(Boolean useExit3)
{
	char *s;

	s = getenv("EF_DUMPCORE");

	if (s != NULL && *s != '\0')
		abort();
	else if (useExit3)
		exit(EXIT_FAILURE);
	else
		_exit(EXIT_FAILURE);
}


