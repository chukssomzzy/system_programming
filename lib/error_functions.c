# include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
# include "tlpi_hdr.h"
# include "ename.c.inc"
static void terminate(Boolean useExit3);
static void outputError(Boolean, int, Boolean, const char *, va_list ap);

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

/**
 * outputError - format error message and print to standard error
 * @useErr: boolean value to determine if the functions uses the
 *	append the errorname and error message to the user string
 * @err: integer that identifies the error
 * @flushStdout: boolean that determines if to flush to stdout
 * @format: format string for the user message
 * @ap: user message list of arguments
 */
void outputError(Boolean useErr, int err, Boolean flushStdout,
		const char *format, va_list ap)
{
# define BUF_SIZE 500
	char err_text[BUF_SIZE], user_msg[BUF_SIZE], buf[BUF_SIZE];

	vsnprintf(user_msg, BUF_SIZE, format, ap);

	if (useErr)
		snprintf(err_text, BUF_SIZE, " [%s %s]",
				((err > 0 && err < MAX_ENAME) ? ename[err] : "?UNKNOWN?"),
				strerror(err));
	else
		snprintf(err_text, BUF_SIZE, ":");

	snprintf_nowarn(buf, BUF_SIZE, "ERROR%s %s\n", err_text, user_msg);

	if (flushStdout)
		fflush(stdout);
	fputs(buf, stderr);
	fflush(stderr);
}

/**
 * errMsg - write formatted errormessage to stderr while flush both stdio and
 *	stderr
 * @format: string literal containing the format string
 */
void errMsg(const char *format, ...)
{
	va_list arg_list;
	int saved_err;

	saved_err = errno;

	va_start(arg_list, format);
	outputError(TRUE, errno, TRUE, format, arg_list);
	va_end(arg_list);

	errno = saved_err;
}

/**
 * errExit - write formatted error message to stderr while flush both stdio and
 *	stderr and exiting the process with exit(3)
 * @format: literal format string
 */
void errExit(const char *format, ...)
{
	va_list arg_list;

	va_start(arg_list, format);
	outputError(TRUE, errno, TRUE, format, arg_list);
	va_end(arg_list);

	terminate(TRUE);
}

/**
 * err_exit - write formatted error message to stderr, not flushing stdio and
 *	exiting with exit(2)
 * @format: format string literal
 */
void err_exit(const char *format, ...)
{
	va_list arg_list;

	va_start(arg_list, format);
	outputError(TRUE, errno, FALSE, format, arg_list);
	va_end(arg_list);

	terminate(FALSE);
}

/**
 * errExitEN - exit process while printing error message to stderr, flushing
 *	stdio.
 * @errnum: error number
 * @format: format string literal
 */
void errExitEN(int errnum, const char *format, ...)
{
	va_list arg_list;

	va_start(arg_list, format);
	outputError(TRUE, errnum, TRUE, format, arg_list);
	va_end(arg_list);

	terminate(TRUE);
}

/**
 * fatal - print format error message to stderr and flush stdio
 * @format: format string literal
 */
void fatal(const char *format, ...)
{
	va_list arg_list;

	va_start(arg_list, format);
	outputError(FALSE, 0, TRUE, format, arg_list);
	va_end(arg_list);

	terminate(TRUE);
}

/**
 * usageErr - print usage error to stderr while flushing stdio
 * @format: format string literal
 */
void usageErr(const char *format, ...)
{
	va_list arg_list;

	fflush(stdin);

	fprintf(stderr, "Usage: ");
	va_start(arg_list, format);
	vfprintf(stderr, format, arg_list);
	va_end(arg_list);

	fflush(stderr); /** incase stderr is not line buffered **/
	exit(EXIT_FAILURE);
}

/**
 * cmdLineErr - print command line usage error to stderr and flush stdin
 * @format: format string literal
 */
void cmdLineErr(const char *format, ...)
{
	va_list arg_list;

	fflush(stdin);

	fprintf(stderr, "Command-line usage error: ");
	va_start(arg_list, format);
	vfprintf(stderr, format, arg_list);
	va_end(arg_list);

	fflush(stderr);
	exit(EXIT_FAILURE);
}
