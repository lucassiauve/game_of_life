#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL_render.h>

enum colors
{
    BLACK = 0x000000,
    GREY = 0x808080,
    WHITE = 0xFFFFFF,
};

// Manage window
int create_window(char *window_title, unsigned int width, unsigned int height,
                  unsigned int cell_size);
void destroy_window();

// Draw
void draw_grid();
void put_cell(int x, int y);
void clear_cell(int x, int y);
void draw_matrix(int new_generation[]);

// Display the current frame
void render_frame();

#endif /* ! GRAPHICS_H */
