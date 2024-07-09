#include "graphics.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_shape.h>
#include <SDL2/SDL_video.h>

#define RED_MASK 0xFF0000
#define GREEN_MASK 0x00FF00
#define BLUE_MASK 0x0000FF

#define EXTRACT_RED(Color) (Color & RED_MASK) >> 16
#define EXTRACT_GREEN(Color) (Color & GREEN_MASK) >> 8
#define EXTRACT_BLUE(Color) (Color & BLUE_MASK)

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

static unsigned int window_width = 0;
static unsigned int window_height = 0;
static unsigned int window_cell_size = 0;

int create_window(char *window_title, unsigned int width, unsigned int height,
                  unsigned int cell_size)
{
    // Create a window
    SDL_Window *tmp_window =
        SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (tmp_window == NULL)
    {
        printf("create_window, failed to create a window: %s", SDL_GetError());
        return -1;
    }

    // Create a renderer
    SDL_Renderer *tmp_renderer = SDL_CreateRenderer(
        tmp_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (tmp_renderer == NULL)
    {
        printf("create_window, failed to create a render: %s", SDL_GetError());
        return -1;
    }

    // Create a texture
    SDL_Texture *tmp_texture =
        SDL_CreateTexture(tmp_renderer, SDL_PIXELFORMAT_ARGB8888,
                          SDL_TEXTUREACCESS_TARGET, width, height);

    // Set global values
    window = tmp_window;
    renderer = tmp_renderer;
    texture = tmp_texture;
    window_width = width;
    window_height = height;
    window_cell_size = cell_size;

    // Set texture as render target
    SDL_SetRenderTarget(renderer, texture);

    return 0;
}

void destroy_window()
{
    if (texture != NULL)
        SDL_DestroyTexture(texture);

    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);

    if (window != NULL)
        SDL_DestroyWindow(window);

    SDL_Quit();
}

/**
 * @brief Set the draw color
 *
 * @param color The color to set
 */
static void set_draw_color(enum colors color)
{
    SDL_SetRenderDrawColor(renderer, EXTRACT_RED(color), EXTRACT_GREEN(color),
                           EXTRACT_BLUE(color), SDL_ALPHA_OPAQUE);
}

/**
 * @brief darw the grid
 *
 */
void draw_grid()
{
    // White back ground
    set_draw_color(WHITE);
    SDL_RenderClear(renderer);

    // Draw grey columns
    set_draw_color(GREY);
    for (unsigned int i = 0; i <= window_width; i += window_cell_size)
    {
        SDL_Rect rect = { .x = i, .y = 0, .w = 1, .h = window_height };
        SDL_RenderFillRect(renderer, &rect);
    }

    // Draw grey lines
    for (unsigned int i = 0; i <= window_height; i += window_cell_size)
    {
        SDL_Rect rect = { .x = 0, .y = i, .w = window_width, .h = 1 };
        SDL_RenderFillRect(renderer, &rect);
    }
}

static void draw_cell(int x, int y, enum colors color)
{
    set_draw_color(color);

    SDL_Rect rect = { .x = x * window_cell_size + 1,
                      .y = y * window_cell_size + 1,
                      .w = window_cell_size - 1,
                      .h = window_cell_size - 1 };
    SDL_RenderFillRect(renderer, &rect);
}

/**
 * @brief Draw and clear cell at x, y
 *
 * @param x The x coordinate
 * @param y The y coordinate
 */
void put_cell(int x, int y)
{
    draw_cell(x, y, BLACK);
}

void clear_cell(int x, int y)
{
    draw_cell(x, y, WHITE);
}

/**
 * @brief Draw cell from matrix
 * 0 do nothing (cell state didnt change),
 * 1 draw cell in black,
 * 2 draw cell in white
 *
 * @param new_generation The matrix to draw
 */
void draw_matrix(int new_generation[])
{
    int nb_row = window_height / window_cell_size;
    int nb_col = window_width / window_cell_size;

    for (int i = 0; i < nb_row; i++)
    {
        for (int j = 0; j < nb_col; j++)
        {
            if (new_generation[i * nb_col + j] == 1)
                put_cell(j, i);
            else if (new_generation[i * nb_col + j] == 2)
                clear_cell(j, i);
        }
    }
}

/**
 * @brief Copy texture to render and display it
 *
 */
void render_frame()
{
    // Set texture as render target
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Display the renderer
    SDL_RenderPresent(renderer);

    // Set texture as render target
    SDL_SetRenderTarget(renderer, texture);
}
