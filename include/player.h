/** @file player.h
 *  @brief Player controller interface.
 *
 *  @author Alexander Patel <acpatel@andrew.cmu.edu>
 *  @bug No known bugs.
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL.h>
#include <stdint.h>

/** @brief structure containing a player's data */
typedef struct {
  double x;  /**< player's x coordinate */
  double y;  /**< player's y coordinage */
  double tx; /**< target x for movement */
  double ty; /**< target y for movement */
} player_t;

void player_init(player_t *player);

void player_handle_event(player_t *player, SDL_Event *e);
void player_move(player_t *player, uint32_t t);

#endif /* _PLAYER_H_ */
