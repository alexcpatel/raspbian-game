/** @file player.c
 *  @brief Player controller implementation.
 *
 *  @author Alexander Patel <acpatel@andrew.cmu.edu>
 *  @bug No known bugs.
 */

#include <SDL.h>
#include <assert.h>
#include <constants.h>
#include <math.h>
#include <player.h>
#include <stdint.h>

const double max_x = (double)(SCREEN_WIDTH - PLAYER_HEIGHT);
const double max_y = (double)(SCREEN_HEIGHT - PLAYER_HEIGHT);

/** @brief Clamps a value within a bound.
 *
 *  @param val The value to clamp
 *  @param lo The low bound of the clamped value
 *  @param hi The high bound of the clamped value
 *
 *  @return val clamped between lo and hi.
 */
static double clamp(double val, double lo, double hi) {
  assert(lo <= hi);

  if (val < lo)
    return lo;
  else if (val > hi)
    return hi;
  return val;
}

/** @brief Initializes a player by setting the position and velocity of the
 *         player to zero.
 *
 *  @param player The player to initialize.
 *  @return Void.
 */
void player_init(player_t *player) {
  assert(player != NULL);

  player->x = 0.0f;
  player->y = 0.0f;
  player->tx = 0.0f;
  player->ty = 0.0f;
}

/** @brief Handles a mouse event for the player.
 *
 *  Sets the new target position for the player's movement.
 *
 *  @param player The player to handle the mouse event for
 *  @param e The SDL event for the player to handle
 *
 *  @return Void.
 */
static void player_handle_mouse(player_t *player, SDL_Event *e) {
  assert(e->type == SDL_MOUSEBUTTONDOWN);

  /* set new target position */
  int tx, ty;
  SDL_GetMouseState(&tx, &ty);
  player->tx = clamp((double)tx, 0, max_x);
  player->ty = clamp((double)ty, 0, max_y);
}

/** @brief Handles an SDL event for the player.
 *
 *  If the SDL event requires no action from the player, this function has no
 *  effect.
 *
 *  @param player The player to handle the SDL event for
 *  @param e The SDL event for the player to handle
 *
 *  @return Void.
 */
void player_handle_event(player_t *player, SDL_Event *e) {
  assert(player != NULL);
  assert(e != NULL);

  switch (e->type) {
  case SDL_MOUSEBUTTONDOWN:
    player_handle_mouse(player, e);
    break;
  default:
    break;
  }
}

/** @brief Moves the player for a given timestep.
 *
 *  @param player The player to move
 *  @param ticks The number of timer ticks to move the player for.
 *
 *  @return Void.
 */
void player_move(player_t *player, uint32_t ticks) {
  assert(player != NULL);
  assert(ticks >= 0);

  double dx, dy, nx, ny, rx, ry, scale;

  /* if the player is in the same pixel as the target, do not move */
  /* this also resolves the special case where pos == target_pos */
  if ((int)player->x == (int)player->tx && (int)player->y == (int)player->ty)
    return;

  /* compute velocity vector direction to target */
  dx = player->tx - player->x;
  dy = player->ty - player->y;

  /* compute updated player position */
  scale = (double)ticks * PLAYER_SPEED / sqrt(abs(dx * dx + dy * dy));
  nx = player->x + dx * scale;
  ny = player->y + dy * scale;

  /* if this movement would pass the target, set the
   * position to the target */
  rx = player->tx - nx;
  ry = player->ty - ny;
  if (rx * dx + ry * dy <= 0.0f) {
    player->x = player->tx;
    player->y = player->ty;
    return;
  }

  /* update player position clamped to the screen */
  player->x = clamp(nx, 0, max_x);
  player->y = clamp(ny, 0, max_y);
}
