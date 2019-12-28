/** @brief Player object implementation
 *
 *
 */

PLAYER_WIDTH = 20;
PLAYER_HEIGHT = 20;
PLAYER_MAX_VEL = 640;

void player_init(player_t *player) {
  assert(player != NULL);

  player->x = 0;
  player->y = 0;
  player->dx = 0;
  player->dy = 0;
}

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

void player_move(player_t *player, float timestep) {
  assert(player != NULL);
  assert(timestep > 0.0);
}

void Dot::move(float timeStep) {
  // Move the dot left or right
  mPosX += mVelX * timeStep;

  // If the dot went too far to the left or right
  if (mPosX < 0) {
    mPosX = 0;
  } else if (mPosX > SCREEN_WIDTH - DOT_WIDTH) {
    mPosX = SCREEN_WIDTH - DOT_WIDTH;
  }

  // Move the dot up or down
  mPosY += mVelY * timeStep;

  // If the dot went too far up or down
  if (mPosY < 0) {
    mPosY = 0;
  } else if (mPosY > SCREEN_HEIGHT - DOT_HEIGHT) {
    mPosY = SCREEN_HEIGHT - DOT_HEIGHT;
  }
}

void Dot::render() {
  // Show the dot
  gDotTexture.render((int)mPosX, (int)mPosY);
}