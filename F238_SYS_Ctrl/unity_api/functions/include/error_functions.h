
#ifndef __ERROR_FUNCTIONS_H__
#define __ERROR_FUNCTIONS_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include "BitVisaType.h"
#define __LOG_FILE
//#define __DEBUG
#ifdef __DEBUG
    #define PRINTF_INFO(format,...) do {\
		debug_in("INFO %s: ", __func__);\
		debug_in(""format"\n", ##__VA_ARGS__);\
	}while(0)

    #define PRINTF(format,...) do {\
		debug_in(""format"", ##__VA_ARGS__);\
	}while(0)

#else
    #define PRINTF(format,...) 
#endif

DiInt32 errSys_in(const char *format, ...);
DiInt32 errUser_in(const char *format, ...);
#define __ERROR
#ifdef __ERROR
    #define errSys(format,...) do {\
		errUser_in("ORROR %s: ", __func__);\
		errSys_in(""format"", ##__VA_ARGS__); \
	} while(0)

    #define errUser(format,...) do {\
		errUser_in("ORROR %s: ", __func__);\
		errUser_in(""format"", ##__VA_ARGS__); \
		errUser_in("\n");\
	} while(0)
#else
    #define errSys(format,...) 
    #define errUser(format,...) 
#endif

#ifdef __cplusplus
    }
#endif

#endif

