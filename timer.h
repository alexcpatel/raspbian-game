/** @brief Timer utility module interface
 *
 *
 */

#include <stdbool.h>
#include <stdint.h>

void timer_start(void);
void timer_stop(void);
void timer_pause(void);
void timer_resume(void);

uint32_t timer_ticks(void);
