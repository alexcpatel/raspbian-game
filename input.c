/** @brief Game input implementation
 *
 *
 */

#include <SDL.h>
#include <input.h>

/** @brief Converts an SDL key event to a game input.
 *
 *  @param input A pointer to the input structure to populate
 *  @param type The type of the SDL key event (as an input_t type)
 *  @param sym The SDL keycode of the key event
 *
 *  @return true if the SDL key event is a valid game input and that input was
 *          copied into the provided structure, or false otherwise.
 */
static bool input_from_key(input_t *input, int type, SDL_Keycode sym) {
  switch (sym) {
  case SDLK_UP:
    input->val = UP;
    break;
  case SDLK_DOWN:
    input->val = DOWN;
    break;
  case SDLK_LEFT:
    input->val = LEFT;
    break;
  case SDLK_RIGHT:
    input->val = RIGHT;
    break;
  default:
    return false;
  }

  input->type = type;
  return true;
}

/** @brief Converts an SDL event to a game input.
 *
 *  @param input A pointer to the input structure to populate
 *  @param ep The SDL event to convert to a game input
 *
 *  @return true if the SDL event is a valid game input and that input was
 *          copied into the provided structure, or false otherwise.
 */
bool input_from_event(input_t *input, SDL_Event *ep) {
  assert(input != NULL);
  assert(ep != NULL);

  /* key was pressed */
  if (ep->type == SDL_KEYDOWN && ep->key.repeat == 0)
    return input_from_key(input, PRESS, ep->key.keysym.sym);
  else if (ep->type == SDL_KEYUP && ep->key.repeat == 0)
    return input_from_key(input, RELEASE, ep->key.keysym.sym);

  return false;
}
