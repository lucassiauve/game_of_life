#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_shape.h>
#include <SDL2/SDL_video.h>

#include "graphics/graphics.h"

#define WINDOW_WIDTH 200
#define WINDOW_HEIGHT 200
#define CELL_SIZE 20

#define FRAME 3000

int main(void)
{
    if (create_window("Game of Life", WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE))
        return -1;

    destroy_window();
}
