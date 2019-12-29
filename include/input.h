/** @file input.h
 *  @brief Game input interface.
 *
 *  @author Alexander Patel <acpatel@andrew.cmu.edu>
 *  @bug No known bugs.
 */

#ifndef _INPUT_H_
#define _INPUT_H_

#include <SDL.h>
#include <stdbool.h>

/* possible types of inputs */
enum { PRESS, RELEASE };
/* possible input values */
enum { UP, DOWN, LEFT, RIGHT };

/* structure containing the data for an input */
typedef struct {
  int type;
  int val;
} input_t;

bool input_from_event(input_t *input, SDL_Event *ep);

#endif /* _INPUT_H_ */
