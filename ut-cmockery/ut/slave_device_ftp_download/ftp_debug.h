#ifndef __FTP_DEBUG_H__
#define __FTP_DEBUG_H__
#include <stdio.h>
#include <stdarg.h>
#include <inttypes.h>

#if defined(SYSTEM_DEBUG)

extern uint32_t get_ftp_dbg(void);
extern void DbgPrintf(uint32_t time, uint32_t sw, const char *fmt, ...);

#define _ftpdebug(time, e_error, fmt, args...) \
    DbgPrintf(time, get_ftp_dbg()&0x3, "%s "fmt, #e_error, ##args);
#elif defined(FTP_DEBUG)
#define _ftpdebug(time, e_error, fmt, args...) \
    printf("%s, %d, %s\n"fmt, __func__, __LINE__, #e_error, ##args)
#else
#define _ftpdebug(time, e_error, fmt, args...) ((void)0)
#endif

#ifdef UT_FTP_DBG
#define _ut_ftpdbg(e_error) printf("%s, %d, %s\n", __func__, __LINE__, #e_error)
#else
#define _ut_ftpdbg(e_error) ((void)0)
#endif

#endif  // FTP_DEBUG_H_
