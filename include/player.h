/** @file player.h
 *  @brief Player controller interface.
 *
 *  @author Alexander Patel <acpatel@andrew.cmu.edu>
 *  @bug No known bugs.
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <input.h>
#include <stdint.h>

/** @brief structure containing a player's data */
typedef struct {
  int x;
  int y;
  int dx;
  int dy;
} player_t;

void player_init(player_t *player);

void player_input(player_t *player, input_t *input);
void player_move(player_t *player, uint32_t timestep);

#endif /* _PLAYER_H_ */
