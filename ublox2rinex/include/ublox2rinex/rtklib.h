#ifndef LITTLERTK_RTKLIB_H
#define LITTLERTK_RTKLIB_H
#include <time.h>
#include <math.h>

typedef struct {        /* time struct */
    time_t time;        /* time (s) expressed by standard time_t */
    double sec;         /* fraction of second under 1 s */
} gtime_t;

extern gtime_t epoch2time(const double *ep);
extern gtime_t gpst2time(int week, double sec);
extern void    time2str(gtime_t t, char *str, int n);
extern void    time2str2(gtime_t t, char *str, int n);
extern void time2epoch(gtime_t t, double *ep);

#endif //LITTLERTK_RTKLIB_H
