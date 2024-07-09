#include <stdio.h>
#include "graphics/graphics.h"
#include "game_rules/game_rules.h"

// Windows variables
#define WINDOW_WIDTH 200
#define WINDOW_HEIGHT 200
#define CELL_SIZE 20

// Time of a frame
#define FRAME 3000

// Grid dimension
#define GRID_ROW WINDOW_HEIGHT / CELL_SIZE
#define GRID_COL WINDOW_WIDTH / CELL_SIZE

// Rule of game
#define UNDERPOPULATION_THRESHOLD 2
#define OVERPOPULATION_THRESHOLD 3
#define REPRODUCTION_THRESHOLD 3

int main(void)
{
    if (create_window("Game of Life", WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE))
        return -1;

    struct grid grid =
    {
        .row = GRID_ROW,
        .col = GRID_COL,
    };

    struct rules rules =
    {
        .die_underpopulation = UNDERPOPULATION_THRESHOLD,
        .die_overpopulation = OVERPOPULATION_THRESHOLD,
        .live_reproduction = REPRODUCTION_THRESHOLD,
    };

    int start_generation[] =
    {
        1,1,1,0,0,0,0,1,1,1,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,1,
        1,1,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        1,1,1,0,0,0,0,1,1,1,
    };

    int next_generation[GRID_ROW * GRID_COL];

    print_generation(grid, start_generation);
    printf("\n");

    build_generation(grid, rules, start_generation, next_generation);

    print_generation(grid, next_generation);
    printf("\n");

    int change_matrix[GRID_ROW * GRID_COL];
    convert_matrix(grid, start_generation, next_generation, change_matrix);

    for (int i = 0; i < grid.row; ++i) 
    {
        for (int j = 0; j < grid.col; ++j)
        {
            printf("|%d", change_matrix[i * grid.col + j]);
        }

        printf("|\n");
    }

    destroy_window();
}
