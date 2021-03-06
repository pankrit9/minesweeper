// Assignment 1 21T2 COMP1511: Minesweeper
// minesweeper.c
//
// This program was written by PANKRIT (z5343191)
// on 1st sept 2021
//
// Version 1.0.0 (2021-06-19): Assignment released.

#include <stdio.h>
#include <stdlib.h>

// Possible square states.
#define VISIBLE_SAFE    0
#define HIDDEN_SAFE     1
#define HIDDEN_MINE     2

// The size of the starting grid.
#define SIZE              8

// The possible command codes.
#define DETECT_ROW      1
#define DETECT_SQUARE   2
#define REVEAL_CROSS    3
#define GAME_MODE       4
#define FLAG_MINE       5
#define DEFUSE          6

// Add any extra #defines here.

void initialise_field(int minefield[SIZE][SIZE]);
void print_debug_minefield(int minefield[SIZE][SIZE]);
void place_mines(int minefield[SIZE][SIZE],int num_mines,int mine_row[num_mines],int mine_col[num_mines]);
int count_mines_row(int minefield[SIZE][SIZE],int row,int col_start,int col_end);
int count_mines_square(int minefield[SIZE][SIZE],int row,int col,int side);



// Place your function prototyes here.

int main(void) {
    int minefield[SIZE][SIZE];

    initialise_field(minefield);
    printf("Welcome to minesweeper!\n");
    printf("How many mines? ");

    // TODO: Scan in the number of pairs of mines.
    int num_mines;
    scanf("%d",&num_mines);

    printf("Enter pairs:\n");
    

    // TODO: Scan in the pairs of mines and place them on the grid.
    // scan locations of mines
    int i=0;
    int mine_row[num_mines];
    int mine_col[num_mines];
    while(i<num_mines)
    {
        scanf("%d %d",&mine_row[i],&mine_col[i]);
        i++;
    }

    // placing them on the grid
    place_mines(minefield,num_mines,mine_row,mine_col);


    printf("Game Started\n");
    print_debug_minefield(minefield);


    // TODO: Scan in commands to play the game until the game ends.
    // A game ends when the player wins, loses, or enters EOF (Ctrl+D).
    // You should display the minefield after each command has been processed.
    int cmd;
    while(scanf("%d",&cmd)==1)
    {
        if(cmd==1)
        {
            int n,row,col_start,col_end;
            scanf("%d",&row);
            scanf("%d",&col_start);
            scanf("%d",&col_end);
            if(row<SIZE && col_start<SIZE && col_end<SIZE && col_start<col_end)
            {
                n=count_mines_row(minefield,row,col_start,col_end);
                printf("There are %d mine(s) in row %d, from column %d to %d\n",n,row,col_start,col_end-1);
                print_debug_minefield(minefield);
            }
            else{
                printf("Coordinates not on the map\n");
                print_debug_minefield(minefield);
            }
        }
        else if(cmd==2)
        {
            int n,row,col,side;
            scanf("%d",&row);
            scanf("%d",&col);
            scanf("%d",&side);
            if(row<SIZE && col<SIZE && side<SIZE)
            {
                n=count_mines_square(minefield,row,col,side);
                printf("There are %d mine(s) in the square centered at row %d, column %d, of size %d\n",n,row,col,side);
                print_debug_minefield(minefield);
            }
            else{
                printf("Coordinated not on the map\n");
                print_debug_minefield(minefield);
            }
        }
        else if(cmd==3)
        {
            int row,col;
            scanf("%d",&row);
            scanf("%d",&col);
            if(minefield[row][col]==HIDDEN_MINE)
            {
                printf("Game over");
                return 0;
            }
            else{
                minefield[row][col]=VISIBLE_SAFE;
                // cases:
                // row,col-1
                // row,col+1
                // row-1,col
                // row+1,col
                // row,col
                if(count_mines_square(minefield,row-1,col,3)==0)
                {
                    minefield[row-1][col]=VISIBLE_SAFE;
                }
                if(count_mines_square(minefield,row+1,col,3)==0)
                {
                    minefield[row+1][col]=VISIBLE_SAFE;
                }
                if(count_mines_square(minefield,row,col-1,3)==0)
                {
                    minefield[row][col-1]=VISIBLE_SAFE;
                }
                if(count_mines_square(minefield,row,col+1,3)==0)
                {
                    minefield[row][col+1]=VISIBLE_SAFE;
                }
            }
            print_debug_minefield(minefield);
        }
    }
    return 0;
}


// Set the entire minefield to HIDDEN_SAFE.
void initialise_field(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            minefield[i][j] = HIDDEN_SAFE;
            j++;
        }
        i++;
    }
}


// Print out the actual values of the minefield.
void print_debug_minefield(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            printf("%d ", minefield[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

// placing the mines on the minefield.
void place_mines(int minefield[SIZE][SIZE],int num_mines,int mine_row[num_mines],int mine_col[num_mines]){
    int i=0;
    int row_index;
    int col_index;
    while(i<num_mines)
    {
        row_index=mine_row[i];
        col_index=mine_col[i];
        minefield[row_index][col_index]=HIDDEN_MINE;
        i++;
    }
}


// counting the mines in a row
int count_mines_row(int minefield[SIZE][SIZE],int row,int col_start,int col_end){
    int num=0;
    int i=col_start;
    while(i<=col_end)
    {
        if(minefield[row][i]==HIDDEN_MINE)
        {
            num++;
        }
        i++;
    }
    return num;
}

// counting the mines in a square
int count_mines_square(int minefield[SIZE][SIZE],int row,int col,int side){
    int num=0;
    int col_i=col-1;
    int col_end=col_i+side-1;
    while(col_i<=col_end && col_i<SIZE)
    {
        int row_i=row-1;
        int row_end=row_i+side-1;
        while(row_i<=row_end && row_i<SIZE)
        {
            if(minefield[row_i][col_i]==HIDDEN_MINE)
            {
                num++;
            }
            row_i++;
        }
        col_i++;
    }
    return num;
}


// Revealing the cross
// void reveal(int minefield[SIZE][SIZE],int row,int col){
//     if(minefield[row][col]==HIDDEN_SAFE)
//     {
//         minefield[row][col]=VISIBLE_SAFE;
//     }
//     int i=row-1;
//     while(i<=row+1 && 0<=i<SIZE)
//     {
//         if(count_mines_row(minefield,i,col,3)==0)
//         {
//             minefield[i][col]=VISIBLE_SAFE;
//         }
//         int j=col-1;
//         i++;
//         while(j<=col+1 && 0<=j<SIZE)
//         {
//             if(count_mines_row(minefield,i,j,3)==0)
//             {
//                 minefield[i][j]=VISIBLE_SAFE;
//                 i++;
//                 j++;
//             }
//             else{
//                 i++;
//             }
//         }
//     }
// }
// row,col-1
// row,col
// row,col+1
// row-1,col
// row+1,col

