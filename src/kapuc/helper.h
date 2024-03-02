#ifndef KAPUC_HELPER_H
#define KAPUC_HELPER_H

#ifdef BENCH_TIMER

#include <time.h>

#define BENCH_TIMER_HELPER(b) clock_t begin = clock(); b clock_t end = clock(); double time_spent = (float)(end - begin) / CLOCKS_PER_SEC; log_info("[BENCH_TIMER] time lexed: %.7f", time_spent);
#else
#define BENCH_TIMER_HELPER(b) b
#endif

#endif //KAPUC_HELPER_H
