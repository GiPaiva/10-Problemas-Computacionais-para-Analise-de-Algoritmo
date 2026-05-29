#include <stdio.h>
#include <string.h>

#define MAX_N 51

int n;
int board[MAX_N];
int cols[MAX_N];
int diag1[2 * MAX_N];
int diag2[2 * MAX_N];
int found;

int isSafe(int row, int col) {
    if (cols[col]) return 0;
    int d1 = row - col + n;
    if (diag1[d1]) return 0;
    int d2 = row + col;
    if (diag2[d2]) return 0;
    return 1;
}

void solve(int row) {
    if (found) return;
    
    if (row == n) {
        found = 1;
        return;
    }
    
    if (board[row] != 0) {
        solve(row + 1);
        return;
    }
    
    for (int col = 1; col <= n; col++) {
        if (isSafe(row, col)) {
            board[row] = col;
            cols[col] = 1;
            diag1[row - col + n] = 1;
            diag2[row + col] = 1;
            
            solve(row + 1);
            
            if (found) return;
            
            board[row] = 0;
            cols[col] = 0;
            diag1[row - col + n] = 0;
            diag2[row + col] = 0;
        }
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(cols, 0, sizeof(cols));
        memset(diag1, 0, sizeof(diag1));
        memset(diag2, 0, sizeof(diag2));
        found = 0;
        
        for (int i = 0; i < n; i++) {
            scanf("%d", &board[i]);
            if (board[i] != 0) {
                cols[board[i]] = 1;
                diag1[i - board[i] + n] = 1;
                diag2[i + board[i]] = 1;
            }
        }
        
        solve(0);
        
        for (int i = 0; i < n; i++) {
            if (i > 0) printf(" ");
            printf("%d", board[i]);
        }
        printf("\n");
    }
    
    return 0;
}
