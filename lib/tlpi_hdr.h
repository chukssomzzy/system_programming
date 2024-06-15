# ifndef __TLPI_HDR_H
# define __TLPI_HDR_H

# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>

# include <unistd.h>
# include <errno.h>
# include <string.h>

# include "get_num.h"

# include "error_functions.h"


typedef enum {
	FALSE, TRUE
} Boolean;

# define min(a, b) ((a) < (b) ? (a) : (b))
# define max(a, b) ((a) > (b) ? (a) : (b))

# endif
