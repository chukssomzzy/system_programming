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

#ifndef __GNUC__
# define snprintf_nowarn snprintf
# else
# define snprintf_nowarn(args...) __extension__({\
		_Pragma("GCC diagnostic push"); \
		_Pragma("GCC diagnostic ignored \"-Wformat-truncation\""); \
		const int _snprintf_nowarn = snprintf(args); \
		_Pragma("GCC diagnostic pop"); \
		_snprintf_nowarn;\
		})
# endif
typedef enum {
	FALSE, TRUE
} Boolean;

# define min(a, b) ((a) < (b) ? (a) : (b))
# define max(a, b) ((a) > (b) ? (a) : (b))

# endif
