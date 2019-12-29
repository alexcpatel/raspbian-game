/** @file timer.h
 *  @brief Global timer interface.
 *
 *  @author Alexander Patel <acpatel@andrew.cmu.edu>
 *  @bug No known bugs.
 */

#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>

void timer_start(void);
void timer_stop(void);
void timer_reset(void);
void timer_pause(void);
void timer_resume(void);

uint32_t timer_ticks(void);

#endif /* _TIMER_H_ */
