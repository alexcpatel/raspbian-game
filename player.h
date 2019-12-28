/** @brief Player object interface
 *
 *
 */

typedef struct {
  int x;
  int y;
  int dx;
  int dy;
} player_t;

typedef enum { UP, LEFT, RIGHT, DOWN } input_t;

void player_init(player_t *player);

void player_input(player_t *player, input_t *input);
void player_move(player_t *player, float timestep);
