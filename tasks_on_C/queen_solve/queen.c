#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isSafe(char **board, int n, int row, int col){
    for(int i = 0; i < row; i++){
        if(board[i][col] == 'Q'){
            return false;
        }
    }

    for(int i = row -1, j = col - 1; i>= 0 && j >= 0; i--, j--){
        if (board[i][j] == 'Q'){
            return false;
        }
    }
    return true;
}

void printBoard(char **board, int n){
    for(int i = 0; i < n; i++){
        for (int j=0; j < n; j++){
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void solveQueens(char **board, int n, int row, int *solutionCount){
    if(row == n){
        printBoard(board, n);
        (*solutionCount)++;
        return;
    }

    for(int col = 0; col < n; col++){
        if(isSafe(board, n, row, col)){
            board[row][col] = 'Q';
            solveQueens(board, n, row + 1, solutionCount);
            board[row][col] = '.';
        }
    }
}

int main(){
    int n;
    printf("Enter board size: ");
    scanf("%d", &n);

    char **board = (char **)malloc(n * sizeof(char *));
    for(int i=0; i<n; i++){
        board[i] = (char *)malloc(n * sizeof(char));
        for(int j=0; j<n; j++){
            board[i][j] = '.';
        }
    }

    int solutionCount = 0;
    solveQueens(board, n, 0, &solutionCount);

    printf("Solves found: %d\n", solutionCount);

    for(int i=0; i<n; i++){
        free(board);

        return 0;
    }
}