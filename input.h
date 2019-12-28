/** @brief Game input interface
 *
 *
 */

#include <SDL.h>

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
