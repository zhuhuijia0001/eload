#ifndef _TRACE_H_
#define _TRACE_H_

extern void rt_kprintf(const char *fmt, ...);

#ifdef RT_DEBUG
#define TRACE(x, arg...)  rt_kprintf(x, ##arg)
#else
#define TRACE(x, arg...)  
#endif

#endif
