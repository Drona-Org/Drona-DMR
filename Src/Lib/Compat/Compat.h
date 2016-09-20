#ifdef PRT_PLAT_LINUXUSER
#define _stricmp strcasecmp
#define LPVOID void*
typedef void *(*start_routine) (void *);
#endif

#if defined(PRT_PLAT_WINUSER)
#include <windows.h>
#elif defined(PRT_PLAT_LINUXUSER)
#include <unistd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

inline void SleepMs(int sleepMs)
{
#if defined(PRT_PLAT_WINUSER)
	Sleep(sleepMs);
#elif defined(PRT_PLAT_LINUXUSER)
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
}

#ifdef __cplusplus
}
#endif