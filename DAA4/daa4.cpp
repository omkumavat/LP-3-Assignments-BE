#include <iostream>
#include <vector>
using namespace std;

// Function to print the chessboard
void printBoard(vector<vector<int>>& board, int n) {
    cout << "\nFinal N-Queens Board Configuration:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << (board[i][j] ? "Q " : ". ");
        cout << endl;
    }
}

// Function to check if a queen can be placed safely at board[row][col]
bool isSafe(vector<vector<int>>& board, int row, int col, int n) {
    // Check this column on upper side
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check upper left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check upper right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// Recursive function to solve N-Queen problem using backtracking
bool solveNQueens(vector<vector<int>>& board, int row, int n) {
    // Base condition: All queens placed
    if (row == n)
        return true;

    // Try placing a queen in each column of current row
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 1; // Place queen

            if (solveNQueens(board, row + 1, n))
                return true; // Recursive call

            board[row][col] = 0; // Backtrack
        }
    }
    return false; // No valid placement found
}

int main() {
    int n, row1, col1;
    cout << "---------------------------------------\n";
    cout << "          N-Queens Problem (Backtracking)\n";
    cout << "---------------------------------------\n";
    cout << "Enter size of chessboard (N): ";
    cin >> n;

    vector<vector<int>> board(n, vector<int>(n, 0));

    cout << "Enter position of first queen (row and column index starting from 0): ";
    cin >> row1 >> col1;

    if (row1 < 0 || col1 < 0 || row1 >= n || col1 >= n) {
        cout << "Invalid position! Try again.\n";
        return 0;
    }

    // Place first queen
    board[row1][col1] = 1;

    // Solve for remaining queens
    bool success = solveNQueens(board, 0, n);

    // Special case: ensure we don’t overwrite the first queen
    if (!success)
        cout << "\nNo solution exists for given configuration.\n";
    else
        printBoard(board, n);

    return 0;
}
