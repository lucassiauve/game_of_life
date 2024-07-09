#ifndef GAME_RULES_H
#define GAME_RULES_H

struct grid
{
    int row;
    int col;
};

struct rules
{
    int die_underpopulation;
    int die_overpopulation;
    int live_reproduction;
};

void build_generation(struct grid grid, struct rules rules, int generation[],
                      int new_generation[]);
void convert_matrix(struct grid grid, int curr_generation[], int next_generation[], int change_matrix[]);
void print_generation(struct grid grid, int generation[]);

#endif /* ! GAME_RULES_H */
