/*
 * @Author: jiejie
 * @Github: https://github.com/jiejieTop
 * @Date: 2019-12-10 22:16:41
 * @LastEditTime : 2019-12-26 00:19:20
 * @Description: the code belongs to jiejie, please keep the author information and source code according to the license.
 */

#include "timer.h"

void platform_timer_init(platform_timer_t* timer)
{
    timer->time = (struct timeval){0, 0};
}

void platform_timer_cutdown(platform_timer_t* timer, unsigned int timeout)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    struct timeval interval = {timeout / 1000, (timeout % 1000) * 1000};
    timeradd(&now, &interval, &timer->time);
}

char platform_timer_is_expired(platform_timer_t* timer)
{
	struct timeval now, res;
	gettimeofday(&now, NULL);
	timersub(&timer->time, &now, &res);
	return ((res.tv_sec < 0) || (res.tv_sec == 0 && res.tv_usec <= 0));
}

int platform_timer_remain(platform_timer_t* timer)
{
	struct timeval now, res;
	gettimeofday(&now, NULL);
	timersub(&timer->time, &now, &res);
	return (res.tv_sec < 0) ? 0 : res.tv_sec * 1000 + res.tv_usec / 1000;
}

