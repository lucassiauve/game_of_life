#include "game_rules.h"

#include <stdio.h>

struct cell
{
    int x;
    int y;
    int alive;
};

static void get_neighborhood_info(struct grid grid, struct cell cell,
                                  int generation[], int *alive)
{
    *alive = 0;

    // Check 9 potential neighborhood
    for (int i = -1; i <= 1; ++i)
    {
        // Cell in edge of grid
        if (cell.x % grid.col == 0 && i == -1)
            continue;
        if (cell.x % grid.col == grid.col -1  && i == 1)
            continue;

        for (int j = -1; j <= 1; ++j)
        {
            // Dont check curr_cell status
            if (i == 0 && j == 0)
                continue;

            // Cell in edge of grid
            if (cell.y % grid.row == 0 && j == -1)
                continue;
            if (cell.y % grid.row == grid.row -1  && j == 1)
                continue;

            *alive += generation[(cell.y + j) * grid.col + cell.x + i];
        }
    }
}

/**
 * @breif Compute the new cell status for next generation
 *
 * @param curr_cell The analysed cell
 * @param generation The matrix of kast generation (1: alive, 0:dead)
 *
 * @return 1 if cell will be alive, 0 if cell will dea
 */
static int new_cell_status(struct grid grid, struct cell curr_cell,
                           struct rules rules, int generation[])
{
    int alive;
    get_neighborhood_info(grid, curr_cell, generation, &alive);

    if (alive < rules.die_underpopulation)
        return 0;

    if (alive > rules.die_overpopulation)
        return 0;

    if (alive == rules.live_reproduction)
        return 1;

    if (curr_cell.alive)
        return 1;
    return 0;
}

/**
 * @breif Build the next generation and store it in new_generation array
 *
 * @param grid Grid demension
 * @param rules Rules of current game
 * @param generation Current generation (start point)
 * @param new_genration New generation build by this function
 */
void build_generation(struct grid grid, struct rules rules, int generation[],
                      int new_generation[])
{
    for (int x = 0; x < grid.col; ++x)
    {
        for (int y = 0; y < grid.row; ++y)
        {
            struct cell curr_cell = { .x = x,
                                      .y = y,
                                      .alive = generation[y * grid.col + x] };

            new_generation[y * grid.col + x] =
                new_cell_status(grid, curr_cell, rules, generation);
        }
    }
}

/**
 * @breif Convert generation matrix in graphic matrix,
 * which only marks cells that have changed state
 *
 * @param grid Grid dimension
 * @param curr_generation Current generation of cells
 * @param next_generation Next generation of cells
 * @param change_matrix Matrix that store cells that have changed state
 */
void convert_matrix(struct grid grid, int curr_generation[], int next_generation[], int change_matrix[])
{
    for (int i = 0; i < grid.col * grid.row; ++i) 
    {
        int new_state = curr_generation[i] - next_generation[i];

        // No change of cell state
        if (new_state == 0)  
            change_matrix[i] = 0;
        
        // Cell alive
        else if (new_state == -1)
            change_matrix[i] = 1;

        // Cell die
        else if (new_state == 1)
            change_matrix[i] = 2;
    }
}

void print_generation(struct grid grid, int generation[])
{
    for (int i = 0; i < grid.row; ++i) 
    {
        for (int j = 0; j < grid.col; ++j)
        {
            printf("|%c", generation[i * grid.col + j] == 0 ? ' ' : 'o');
        }

        printf("|\n");
    }
}
