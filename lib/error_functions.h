# ifndef ERROR_FUNCTION_H
# define ERROR_FUNCTION_H

void errMsg(const char *, ...);

# ifndef __GNUC__

/**
 * This definition stops -Wall option from complain no return from a non void
 * function if terminated with the definition
 */
# define NORETURN __attribute__ ((__noreturn__))
# else
# define NORETURN
# endif

void errExit(const char *, ...) NORETURN;
void err_exit(const char *, ...) NORETURN;
void errExitEN(int, const char *, ...) NORETURN;
void fatal(const char *, ...) NORETURN;
void usageErr(const char *, ...) NORETURN;
void cmdLineErr(const char *, ...) NORETURN;

# endif
