/** @file game.c
 *  @brief A simple game...
 *
 *  @author Alexander Patel <acpatel@andrew.cmu.edu>
 *  @bug No known bugs.
 */

#include <SDL.h>
#include <SDL_image.h>
#include <constants.h>
#include <input.h>
#include <player.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <texture.h>
#include <timer.h>

/** @brief the name of the game, to be displayed in the window header */
static const char *game_name = "test game";
/** @brief the name of the image file to load for the player texture */
static const char *player_tex_path = "dot.bmp";

/** @brief window to render to */
static SDL_Window *window = NULL;
/** @brief texture renderer */
static SDL_Renderer *rend = NULL;
/** @brief player texture */
static texture_t player_tex;

bool game_init(void);
void game_close(void);
void game_loop(void);

/** @brief Initializes the game state
 *
 *  This function initializes SDL, sets texture filtering to linear,
 *  creates a window to render on, creates a renderer for the window,
 *  initializes the render color to white, initializes PNG loading,
 *  and loads the texture for the player.
 *
 *  @return true if the steps listed all completed successfully,
 *          or false otherwise,
 */
bool game_init(void) {
  /* initialize SDL */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    goto init_err;
  }

  /* set texture filtering to linear */
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    printf("Warning: Linear texture filtering not enabled!");

  /* create window to render on */
  window = SDL_CreateWindow(game_name, SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Window could not be created! Error: %s\n", SDL_GetError());
    goto init_err;
  }

  /* create renderer for window */
  rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (rend == NULL) {
    printf("Renderer could not be created! Error: %s\n", SDL_GetError());
    goto init_err_window;
  }

  /* initialize renderer color to white */
  SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);

  /* initialize PNG loading */
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    printf("SDL_image could not initialize! Error: %s\n", IMG_GetError());
    goto init_err_rend;
  }

  /* create and load player texture */
  texture_init(&player_tex);
  if (!texture_load(&player_tex, rend, player_tex_path)) {
    printf("Failed to load dot texture!\n");
    goto init_err_rend;
  }

  return true;

  /* error cleanup */
init_err_rend:
  SDL_DestroyRenderer(rend);
init_err_window:
  SDL_DestroyWindow(window);
init_err:
  return false;
}

/** @brief Closes the game by freeing resources and exiting.
 *
 *  @return Does not return, exits the process with status 0.
 */
void game_close() {
  /* free resources */
  texture_destroy(&player_tex);
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(window);

  /* close SDL and IMG modules */
  IMG_Quit();
  SDL_Quit();

  /* exit the program */
  exit(0);
}

/** @brief Performs the game loop, which polls for SDL events and updates the
 *         game state.
 *
 *  @return Does not return, unless the game is quit.
 */
void game_loop() {
  SDL_Event e;
  input_t input;
  player_t player;

  /* initialize game loop */
  player_init(&player);
  timer_start();

  while (true) {
    /* handle all pending SDL events */
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        game_close();
      if (input_from_event(&input, &e))
        player_input(&player, &input);
    }

    /* move player */
    player_move(&player, timer_ticks() / 7);
    timer_reset();

    /* render player */
    SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(rend);
    texture_render(&player_tex, rend, player.x, player.y);
    SDL_RenderPresent(rend);
  }
}

/** @brief main routine of the game program */
int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  /* initialize game state */
  if (!game_init()) {
    printf("Failed to initialize!\n");
    return -1;
  }

  /* begin game loop */
  game_loop();
  return 0;
}
