#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define coor_t int
enum direction_t
{
    UP, DOWN, LEFT, RIGHT
};

#define BREAK 1
#define REPEAT 0
#define GAME_OVER - 1
#define DEFAULT_DIM 4
#define SAVE_FILE_NAME "saveFile.txt"

typedef struct context
{
    coor_t base_y;
    coor_t base_x;

    int dim;
    int size;
    int *grid;

    int score;
    int added_score;
}
game_context;

void resetGridAndScore(game_context *g_ctx)
{
    memset(g_ctx->grid, 0, g_ctx->size *4);
    g_ctx->score = 0;
}

game_context* initGameContext(coor_t base_y, coor_t base_x, int dim)
{
    game_context *g_ctx = (game_context*) malloc(sizeof(game_context));

    g_ctx->base_y = base_y;
    g_ctx->base_x = base_x;

    g_ctx->dim = dim;
    g_ctx->size = dim * dim;
    g_ctx->grid = (int*) malloc(sizeof(int) *g_ctx->size);

    resetGridAndScore(g_ctx);

    return g_ctx;
}

void freeGameContext(game_context **g_ctx)
{
    free((*g_ctx)->grid);
    free(*g_ctx);
}

int getIndex(game_context *g_ctx, coor_t y, coor_t x)
{
    return y *g_ctx->dim + x;
}

int newNumber()
{
    return rand() % 2 == 0 ? 2 : 4;
}

int newCoordinate(game_context *g_ctx)
{
    return rand() % g_ctx->dim;
}

int yCoor(game_context *g_ctx, coor_t y)
{
    return g_ctx->base_y + 1 + y * 2;
}

int xCoor(game_context *g_ctx, coor_t x)
{
    return g_ctx->base_x + 1 + x * 5;
}

void drawCell(game_context *g_ctx, coor_t y, coor_t x)
{
    int number = g_ctx->grid[getIndex(g_ctx, y, x)];

    move(yCoor(g_ctx, y), xCoor(g_ctx, x));
    if (number == 0)
    {
        printw("    ");
        return;
    }

    int color = 0;
    while (number != 1)
    {
        number >>= 1;
        color++;
    }
    attron(COLOR_PAIR(color));
    printw("%4d", g_ctx->grid[getIndex(g_ctx, y, x)]);
    attroff(COLOR_PAIR(color));

}

void drawGrid(game_context *g_ctx)
{
    int i;

    char *horizontal = (char*) malloc(g_ctx->dim *5 + 1);
    char *vertical = (char*) malloc(g_ctx->dim *5 + 1);
    strcpy(horizontal, "=");
    strcpy(vertical, "|");
    for (i = 0; i < g_ctx->dim; i++)
    {
        strcat(horizontal, "=====");
        strcat(vertical, "    |");
    }

    for (i = 0; i < g_ctx->dim; i++)
    {
        move(g_ctx->base_y + (i << 1), g_ctx->base_x);
        printw("%s\n", horizontal);
        move(g_ctx->base_y + (i << 1) + 1, g_ctx->base_x);
        printw("%s\n", vertical);
    }
    move(g_ctx->base_y + (i << 1), g_ctx->base_x);
    printw("%s\n", horizontal);

    free(horizontal);
    free(vertical);
}

void initScreen(game_context *g_ctx)
{

    initscr();
    noecho();
    cbreak();

    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_CYAN);
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);
    init_pair(3, COLOR_YELLOW, COLOR_RED);
    init_pair(4, COLOR_RED, COLOR_BLUE);
    init_pair(5, COLOR_BLUE, COLOR_GREEN);
    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    init_pair(8, COLOR_MAGENTA, COLOR_YELLOW);
    init_pair(9, COLOR_BLUE, COLOR_RED);
    init_pair(10, COLOR_BLACK, COLOR_CYAN);
    init_pair(11, COLOR_YELLOW, COLOR_MAGENTA);

    drawGrid(g_ctx);

    move(g_ctx->base_y + 1, g_ctx->base_x + g_ctx->dim *5 + 10);
    printw("(r) - restart");
    move(g_ctx->base_y + 3, g_ctx->base_x + g_ctx->dim *5 + 10);
    printw("(c) - save");
    move(g_ctx->base_y + 5, g_ctx->base_x + g_ctx->dim *5 + 10);
    printw("(l) - load");
    move(g_ctx->base_y + 7, g_ctx->base_x + g_ctx->dim *5 + 10);
    printw("(q) - quit");

}

void placeNewNumber(game_context *g_ctx)
{

    coor_t y, x;
    while (1)
    {
        y = newCoordinate(g_ctx);
        x = newCoordinate(g_ctx);

        if (!g_ctx->grid[getIndex(g_ctx, y, x)])
        {
            g_ctx->grid[getIndex(g_ctx, y, x)] = newNumber();
            drawCell(g_ctx, y, x);
            break;
        }
    }
    refresh();
}

void printScore(game_context *g_ctx)
{
    move(g_ctx->base_y - 1, g_ctx->base_x);
    clrtoeol();
    move(g_ctx->base_y - 1, g_ctx->base_x);
    printw("Score: %d", g_ctx->score);

    if (g_ctx->added_score != 0)
    {
        printw(" ");
        attron(COLOR_PAIR(3));
        printw("+ ");
        printw("%d", g_ctx->added_score);
        attroff(COLOR_PAIR(3));
    }
}

void updateRow(game_context *g_ctx, int *row, int *status)
{

    int i, j;
    int merged[g_ctx->dim];
    memset(merged, 0, g_ctx->dim *4);

    for (i = 0; i < g_ctx->dim; i++)
    {
        for (j = i + 1; j < g_ctx->dim; j++)
        {
            if (row[j] == 0) continue;
            else if (row[i] == 0 && row[j] > 0)
            {
                row[i] = row[j];
                row[j] = 0;
                j--;
                *status = BREAK;
            }
            else if (row[i] != row[j]) break;
            else if (row[i] == row[j] && !merged[i])
            {
                row[i] *= 2;
                row[j] = 0;
                merged[i] = 1;
                *status = BREAK;
                g_ctx->added_score += row[i];
            }
        }
    }
}

int redrawGrid(game_context *g_ctx)
{
    int y, x;
    int num_full_cells = 0;
    for (y = 0; y < g_ctx->dim; y++)
    {
        for (x = 0; x < g_ctx->dim; x++)
        {
            drawCell(g_ctx, y, x);
            if (g_ctx->grid[getIndex(g_ctx, y, x)]) num_full_cells++;
        }
    }
    refresh();
    return num_full_cells;
}

int moveTiles(game_context *g_ctx, enum direction_t direction)
{
    int y, x;

    int status = REPEAT;
    int row[g_ctx->dim];
    g_ctx->added_score = 0;

    if (direction == UP || direction == DOWN)
    {
        for (x = 0; x < g_ctx->dim; x++)
        {
            for (y = 0; y < g_ctx->dim; y++)
                row[y] = g_ctx->grid[getIndex(g_ctx, direction == UP ? y : g_ctx->dim - 1 - y, x)];
            updateRow(g_ctx, row, &status);
            for (y = 0; y < g_ctx->dim; y++)
                g_ctx->grid[getIndex(g_ctx, direction == UP ? y : g_ctx->dim - 1 - y, x)] = row[y];
        }
    }
    else if (direction == LEFT || direction == RIGHT)
    {
        for (y = 0; y < g_ctx->dim; y++)
        {
            for (x = 0; x < g_ctx->dim; x++)
                row[x] = g_ctx->grid[getIndex(g_ctx, y, direction == LEFT ? x : g_ctx->dim - 1 - x)];
            updateRow(g_ctx, row, &status);
            for (x = 0; x < g_ctx->dim; x++)
                g_ctx->grid[getIndex(g_ctx, y, direction == LEFT ? x : g_ctx->dim - 1 - x)] = row[x];
        }
    }

    status = redrawGrid(g_ctx) == g_ctx->size ? GAME_OVER : status;
    g_ctx->score += g_ctx->added_score;

    return status;
}

void saveGame(game_context *g_ctx)
{

    int i, j;

    FILE * fp;
    fp = fopen(SAVE_FILE_NAME, "w");

    fprintf(fp, "%d\n", g_ctx->dim);
    fprintf(fp, "%d\n", g_ctx->score);

    for (i = 0; i < g_ctx->dim; i++)
    {
        for (j = 0; j < g_ctx->dim; j++)
        {
            fprintf(fp, j == g_ctx->dim - 1 ? "%4d\n" : "%4d,", g_ctx->grid[getIndex(g_ctx, i, j)]);
        }
    }

    fclose(fp);
}

void loadGame(game_context *g_ctx)
{

    if (access(SAVE_FILE_NAME, F_OK) == -1)
    {
        return;
    }

    int i, j;

    char *token;
    char *line = (char*) malloc(sizeof(char) *g_ctx->dim *5 + 1);

    FILE * fp;
    fp = fopen(SAVE_FILE_NAME, "r");

    fgets(line, 5, fp);
    g_ctx->dim = atoi(line);
    fgets(line, 10, fp);
    g_ctx->score = atoi(line);
    g_ctx->size = g_ctx->dim *g_ctx->dim;

    free(g_ctx->grid);
    g_ctx->grid = (int*) malloc(sizeof(int) *g_ctx->size);

    for (i = 0; i < g_ctx->dim; i++)
    {

        fgets(line, g_ctx->dim *5 + 1, fp);

        token = strtok(line, ",");
        g_ctx->grid[getIndex(g_ctx, i, 0)] = atoi(token);
        for (j = 1; j < g_ctx->dim; j++)
        {
            token = strtok(NULL, ",");

            g_ctx->grid[getIndex(g_ctx, i, j)] = atoi(token);
        }
    }
    free(line);

    fclose(fp);
}
int playerMove(game_context *g_ctx)
{
    char input;
    int result;
    while (1)
    {
        flushinp();
        input = getch();

        if (input == 'w' || input == 's' || input == 'a' || input == 'd')
        {

            enum direction_t direction;
            if (input == 'w') direction = UP;
            else if (input == 's') direction = DOWN;
            else if (input == 'a') direction = LEFT;
            else direction = RIGHT;
            result = moveTiles(g_ctx, direction);
            if (result == BREAK) break;
            else if (result == GAME_OVER) return 1;
        }
        else if (input == 'r')
        {
            resetGridAndScore(g_ctx);
            redrawGrid(g_ctx);
            placeNewNumber(g_ctx);
            break;
        }
        else if (input == 'c')
        {
            saveGame(g_ctx);
        }
        else if (input == 'l')
        {
            loadGame(g_ctx);
            printScore(g_ctx);
            redrawGrid(g_ctx);
        }
        else if (input == 'q')
        {
            return 1;
        }
    }
    return 0;
}

void gameLoop(game_context *g_ctx)
{
    placeNewNumber(g_ctx);
    while (1)
    {
        placeNewNumber(g_ctx);
        printScore(g_ctx);
        if (playerMove(g_ctx)) return;
    }
}

void play2048(int dim)
{

    srand(time(NULL));

    game_context *g_ctx = initGameContext(10, 10, dim);
    initScreen(g_ctx);

    gameLoop(g_ctx);

    endwin();
    freeGameContext(&g_ctx);
}

int main(int argc, char *argv[])
{
    int dim = DEFAULT_DIM;
    if (argc == 2)
    {
        dim = atoi(argv[1]);
    }
    play2048(dim);
    return (0);
}