/** @brief Texture utility module implementation
 *
 *
 */

#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <texture.h>

/** @brief Initializes a texture.
 *
 *  @param tex A pointer to the texture to initialize
 */
void texture_init(texture_t *tex) {
  assert(tex != NULL);

  tex->w = 0;
  tex->h = 0;
  tex->sdltex = NULL;
}

/** @brief Destroys a texture, freeing its data, and allowing it to be
 *         re-initialized.
 *
 *  @param tex A pointer to the texture to destroy
 */
void texture_destroy(texture_t *tex) {
  assert(tex != NULL);
  assert(tex->sdltex != NULL);

  SDL_DestroyTexture(tex->sdltex);
  tex->sdltex = NULL;
  tex->w = 0;
  tex->h = 0;
}

/** @brief Loads a texture from a filepath.
 *
 *  @param tex A pointer to the texture to load an image to
 *  @param rend The SDL renderer to use to load the image
 *  @param path A path to the image file to load
 *
 *  @return true if loading the image into the texture succeeded,
 *          or false otherwise.
 */
bool texture_load(texture_t *tex, SDL_Renderer *rend, const char *path) {
  assert(tex != NULL);
  assert(rend != NULL);
  assert(path != NULL);
  assert(tex->sdltex != NULL);

  SDL_Surface *surf;
  SDL_Texture *sdltex;

  /* load image into new surface */
  if ((surf = IMG_Load(path)) == NULL) {
    printf("Unable to load image %s! Error: %s\n", path, IMG_GetError());
    return false;
  }

  /* create texture from surface pixels */
  if ((sdltex = SDL_CreateTextureFromSurface(rend, surf)) == NULL) {
    printf("Unable to create texture! Error: %s\n", SDL_GetError());
    SDL_FreeSurface(surf);
    return false;
  }

  /* populate texture fields with loaded image */
  tex->sdltex = sdltex;
  tex->w = surf->w;
  tex->h = surf->h;

  SDL_FreeSurface(surf);
  return true;
}

/** @brief Renders a texture to an SDL renderer.
 *
 *  @param tex A pointer to the texture to render
 *  @param rend The SDL renderer to use to render the texture
 *  @param x The x coordinate to render at
 *  @param y The y coordinate to render at
 */
void texture_render(texture_t *tex, SDL_Renderer *rend, int x, int y) {
  assert(tex != NULL);
  assert(rend != NULL);
  assert(tex->sdltex != NULL);

  /* set rendering space and render */
  SDL_Rect quad = {x, y, tex->w, tex->h};
  SDL_RenderCopy(rend, tex->sdltex, NULL, &quad);
}
