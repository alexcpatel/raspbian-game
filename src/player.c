/** @file player.c
 *  @brief Player controller implementation.
 *
 *  @author Alexander Patel <acpatel@andrew.cmu.edu>
 *  @bug No known bugs.
 */

#include <assert.h>
#include <constants.h>
#include <input.h>
#include <player.h>
#include <stdint.h>

/** @brief Initializes a player by setting the position and velocity of the
 *         player to zero.
 *
 *  @param player The player to initialize.
 *  @return Void.
 */
void player_init(player_t *player) {
  assert(player != NULL);

  player->x = 0;
  player->y = 0;
  player->dx = 0;
  player->dy = 0;
}

/** @brief Handles an input for the player.
 *
 *  This function updates the velocity of the player based on the type
 *  (pressed/released) and value (direction) of the input.
 *
 *  @param player The player to handle the input for.
 *  @param input The input to handle for the player.
 *
 *  @return Void.
 */
void player_input(player_t *player, input_t *input) {
  assert(player != NULL);
  assert(input != NULL);
  assert(input->type == PRESS || input->type == RELEASE);

  int d = input->type == PRESS ? 1 : 0;
  switch (input->val) {
  case UP:
    player->dy = -d;
    break;
  case DOWN:
    player->dy = d;
    break;
  case LEFT:
    player->dx = -d;
    break;
  case RIGHT:
    player->dx = d;
    break;
  default:
    assert(input->val == UP || input->val == DOWN || input->val == LEFT ||
           input->val == RIGHT);
  }
}

/** @brief Clamps an integer in a bound.
 *
 *  @param val The value to clamp
 *  @param lo The low bound of the clamped value
 *  @param hi The high bound of the clamped value
 *
 *  @return val clamped between lo and hi.
 */
static int clamp(int val, int lo, int hi) {
  assert(lo <= hi);

  if (val < lo)
    return lo;
  else if (val > hi)
    return hi;
  return val;
}

/** @brief Moves the player for a given timestep.
 *
 *  @param player The player to move
 *  @param timestep The number of timer ticks to move the player for.
 *
 *  @return Void.
 */
void player_move(player_t *player, uint32_t timestep) {
  assert(player != NULL);
  assert(timestep >= 0);

  /* update x position */
  player->x += player->dx * timestep;
  player->x = clamp(player->x, 0, SCREEN_WIDTH - PLAYER_HEIGHT);

  /* update y position */
  player->y += player->dy * timestep;
  player->y = clamp(player->y, 0, SCREEN_HEIGHT - PLAYER_HEIGHT);
}
