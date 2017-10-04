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
typedef struct cell{
  char current;
  char next;
} cell;

/* Declaration of functions */
void initField(const int rows, const int cols, cell field[rows][cols]);
void loadGlider(const int rows, const int cols, cell field[rows][cols]);
void loadSemaphore(const int rows, const int cols, cell field[rows][cols]);
void loadRandom(const int rows, const int cols, cell field[rows][cols]);
void loadCustom(const int rows, const int cols, cell field[rows][cols]);

/* My (Buster) functions */
int checkNeighboors (const int rows, const int cols, int x, int y, cell field[20][20]);
int isAlive (char status, int aliveCells);

void calculateNextGeneration (const int rows, const int cols, cell field[rows][cols]);
void replaceCells (const int rows, const int cols, cell field[rows][cols]);
void printCells (const int rows, const int cols, cell field[rows][cols]);


/* Function:    main
 * Description: Start and run games, interact with the user.
 * Input:       About what initial structure and whether to step or exit.
 * Output:      Information to the user, and the game field in each step.
 */

int main(void) {

    char userInput;
	
	//rows and cols are hardcoded, but can easily be changed
    int rows = 20;
    int cols = 20;
	
	//Initiates field array witch size of rows and cols
    cell field[rows][cols];

    initField(rows, cols, field);

    do {
        
        printCells(rows, cols, field);
        calculateNextGeneration(rows, cols, field);
        replaceCells(rows, cols, field);
		
		printf("Select one of the following options:\n");
		printf("        (enter) Step\n");
		printf("        (any)   Exit\n");
        scanf("%c", &userInput);
		
    } while (userInput == '\n');
    

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
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {

            random = rand() % 2;
            if (random == 1) {
				field[r][c].current = ALIVE;
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


/* Function:    calculateNextGeneration
 * Description: Calculates the next generation of cells compared to current one
 * Input:       The field array and it's size
 * Output:      Points back to cells in field array and change value to
				either DEAD or ALIVE
 */
void calculateNextGeneration(const int rows, const int cols, cell field[rows][cols]) {
	
    int aliveCells = 0;
    for (int r = 0; r < rows; r++) {

        for (int c = 0; c < cols; c++) {

            aliveCells = checkNeighboors(rows, cols, r, c, field);
            field[r][c].next = isAlive(field[r][c].current, aliveCells);
        }
    }
}


/* Function:    checkNeighboors
 * Description: Check the neighboors of current cell so see how many are alive.
 * Input:       Current cell x and y position, field array and it's lengh
 * Output:      Return int of how many cell neighboors are alive
 */
int checkNeighboors(const int rows, const int cols, int x, int y, cell field[rows][cols]) {
	
    int aliveCells = 0;
	
	//2 for loops, looping through the 9 cells (including current) that
	//are around current one.
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {

			//Checks that cell is not the current cell
            if ( !((x - 1 + r == x) && (y - 1 + c == y)) &&
			//Checks that cell is defined within array:
			// 0 >= x < number of rows
			// 0 >= y < number of cols
                (x - 1 + r >= 0) &&
                (x - 1 + r < rows)&&
                (y - 1 + c >= 0) &&
                (y - 1 + c < cols)) {
				
                if (field[x - 1 + r][y - 1 + c].current == ALIVE) {

                    aliveCells = aliveCells + 1;
                }
            }
        }
    }
	
    return aliveCells;
}


/* Function:    isAlive
 * Description: Checks wheather or not cell will live to the next generation
 * Input:       Current status of cell (dead/alive), how many living neighboors
				it has
 * Output:      Returns status of DEAD or ALIVE
 */
int isAlive(char status, int aliveCells) {
	
    char newStatus;
    
	//Dead cells -> ALIVE
    if (status == DEAD && aliveCells == 3) {

        newStatus = ALIVE;
	
	//Alive cells -> ALIVE
    } else if (status == ALIVE && aliveCells > 1 && aliveCells < 4) {
		
        newStatus = ALIVE;
		
	//Dead and alive cells -> DEAD
    } else {

        newStatus = DEAD;
    }

    return newStatus;
}


/* Function:    replaceCells
 * Description: Replacing the old generation of cells with new calculation
				each "current" cell is replaced with "next" cell
 * Input:       The field array and its size
 * Output:      Points back to array and changes value
 */
void replaceCells(const int rows, const int cols, cell field[rows][cols]) {
	
    for (int r = 0; r < rows; r++) {

        for (int c = 0; c < cols; c++) {
			
            field[r][c].current = field[r][c].next;
        }
    }
}


/* Function:    printCellls
 * Description: Prints alive and dead cells on screen
 * Input:       The field array and its size
 * Output:      None
 */
void printCells(int rows, int cols, cell field[rows][cols]) {   

    for (int r = 0; r < rows; r++) {

        for (int c = 0; c < cols; c++) {

            printf("%c ", field[r][c].current);
        }

        printf("\n");
    }
}