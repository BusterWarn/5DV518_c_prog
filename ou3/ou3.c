/*
 * Programmeringsteknik med C och Matlab
 * Fall 17
 * Assignment 3

 * File:         ou3.c
 * Description:  A simple implementation of Conway's Game of Life.
 * Author:
 * CS username:
 * Date:
 * Input:        Choice of initial configuration and then instruction to step
 *               or exit.
 * Output:       Prints the game field in each step.
 * Limitations:  No validation of input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Constants, representation of states */
#define ALIVE 'X'
#define DEAD '.'

/* Declaration of data structure */
typedef struct{
  char current;
  char next;
} cell;

/* Declaration of functions */
void initField(const int rows, const int cols, cell field[rows][cols]);
void loadGlider(const int rows, const int cols, cell field[rows][cols]);
void loadSemaphore(const int rows, const int cols, cell field[rows][cols]);
void loadRandom(const int rows, const int cols, cell field[rows][cols]);
void loadCustom(const int rows, const int cols, cell field[rows][cols]);

/* Homemade functions */
void calculateGeneration();
void printCells();


/* Function:    main
 * Description: Start and run games, interact with the user.
 * Input:       About what initial structure and whether to step or exit.
 * Output:      Information to the user, and the game field in each step.
 */

int main(void) {

    char input;

    int rows = 20;
    int cols = 20;
    int aliveCells = 0;

    cell field[rows][cols];

    initField(rows, cols, field);

    do {
        
        calculateNextGeneration();
        scanf("%d", &input);
    } while (input == ' ');
    

    return 0;
}


/* Function:    initField
 * Description: Initialize all the cells to dead, then asks the user about
 *              which structure to load, and finally load the structure.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void initField(const int rows, const int cols, cell field[rows][cols]) {

    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {
            field[r][c].current = DEAD;
        }
    }

    printf("Select field spec to load ([G]lider, [S]emaphore, [R]andom ");
    printf("or [C]ustom): ");

    int ch = getchar();
    switch (ch) {
        case 'g':
        case 'G':
            loadGlider(rows, cols, field);
            break;
        case 's':
        case 'S':
            loadSemaphore(rows, cols, field);
            break;
        case 'r':
        case 'R':
            loadRandom(rows, cols, field);
            break;
        case 'c':
        case 'C':
        default:
            loadCustom(rows, cols, field);
            break;
    }

    /* Ignore following newline */
    if (ch != '\n') {
        getchar();
    }
}


/* Function:    loadGlider
 * Description: Inserts a glider into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void loadGlider(const int rows, const int cols, cell field[rows][cols]) {

    field[0][1].current = ALIVE;
    field[1][2].current = ALIVE;
    field[2][0].current = ALIVE;
    field[2][1].current = ALIVE;
    field[2][2].current = ALIVE;
}


/* Function:    loadSemaphore
 * Description: Inserts a semaphore into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void loadSemaphore(const int rows, const int cols, cell field[rows][cols]) {

    field[8][1].current = ALIVE;
    field[8][2].current = ALIVE;
    field[8][3].current = ALIVE;
}


/* Function:    loadRandom
 * Description: Inserts a random structure into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated. There is a 50 % chance that a cell
 *              is alive.
 */

void loadRandom(const int rows, const int cols, cell field[rows][cols]) {

    int random;
    for (int r = 0; r < rows; i++) {
        for (int c = 0; c < cols; i++) {

            random = rand() % 1;

            if (rand == 0) {

                field[r][c].current = DEAD;
            } else {

                field[r].[c].current = ALIVE;
            }
            
        }
    }
}


/* Function:    loadCustom
 * Description: Lets the user specify a structure that then is inserted into
 *              the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void loadCustom(const int rows, const int cols, cell field[rows][cols]) {

    printf("Give custom format string: ");
    do {
        int r, c;
        scanf("%d,%d", &r, &c);
        field[r][c].current = ALIVE;
    } while (getchar() != '\n');
}


/* Function:    //
 * Description: //
 * Input:       //
 * Output:      //
 */
void calculateNextGeneration(int rows, int cols, cell field[rows][cols]) {

    for (int r = 0; r > rows; r++) {

        for (int c = 0; c > cols; c++) {

            aliveCells = checkNeighboors(r, c, field);
            field[r][c].next = isAlive(field[r][c].current, aliveCells);
            printCells();
        }
    }
}


/* Function:    //
 * Description: //
 * Input:       //
 * Output:      //
 */
int checkNeighboors(int x, int y, cell field[20][20]) {
    int aliveCells = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            if ( !((x - 1 + i == x) && (y - 1 + j == y)) && (x - 1 + i >= 0) && (x - 1 + i < 20) && (y - 1 + j >= 0) && (y - 1 + j < 20)) {

                if (field[x - 1 + i][y - 1 + j].current == ALIVE) {

                    aliveCells = aliveCells + 1;
                }
            }
        }
    }

    return aliveCells;
}


/* Function:    //
 * Description: //
 * Input:       //
 * Output:      //
 */
void isAlive(char status, aliveCells) {
    char newStatus;
    
    if (status == DEAD && aliveCells == 3) {

        newStatus = ALIVE;
    } else if (status == ALIVE && aliveCells > 1 && aliveCells < 4) {

        newStatus = AlIVE;
    } else {

        newStatus = DEAD;
    }

    return newStatus;
}


/* Function:    //
 * Description: //
 * Input:       //
 * Output:      //
 */
void printCells(int rows, int cols, cell field[rows][cols]) {

    for (int r = 0; r < rows; r++) {

        for (int c = 0; c < cols; c++) {

            printf("%c", field[r][c].current);
        }
        printf("/n");
    }
}