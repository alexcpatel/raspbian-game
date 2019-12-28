/** @brief Texture utility module interface
 *
 *
 */

#include <SDL.h>
#include <SDL_image.h>

/** @brief structure containing a texture's data */
typedef struct {
  int w;               /**< width of the texture */
  int h;               /**< height of the texture */
  SDL_Texture *sdltex; /**< the SDL texture*/
} texture_t;

void texture_init(texture_t *tex);
void texture_destroy(texture_t *tex);

bool texture_load(texture_t *tex, SDL_Renderer *rend, const char *path);
void texture_render(texture_t *tex, SDL_Renderer *rend, int x, int y);
