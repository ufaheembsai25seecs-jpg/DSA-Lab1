#include <iostream>
#include <iomanip>
using namespace std;

const int MAX_N = 8;

// eight possible knight moves
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// check if cell is inside and empty
bool isValid(int x, int y, int n, int board[][MAX_N]) {
    return (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == -1);
}

// count available moves from (x, y)
int getDegree(int x, int y, int n, int board[][MAX_N]) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (isValid(x + dx[i], y + dy[i], n, board)) {
            count++;
        }
    }
    return count;
}

// recursive backtracking solver
bool solveKnightTour(int x, int y, int moveNumber, int n, int board[][MAX_N]) {
    board[x][y] = moveNumber; // mark current square

    // base case: all squares visited
    if (moveNumber == n * n) return true;

    // find candidate moves and their degrees
    int nextMoves[8];
    int degrees[8];
    int numCandidates = 0;

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isValid(nx, ny, n, board)) {
            nextMoves[numCandidates] = i;
            degrees[numCandidates] = getDegree(nx, ny, n, board);
            numCandidates++;
        }
    }

    // sort candidate moves by degree (Warnsdorff heuristic)
    for (int i = 0; i < numCandidates - 1; i++) {
        for (int j = i + 1; j < numCandidates; j++) {
            if (degrees[j] < degrees[i]) {
                swap(degrees[i], degrees[j]);
                swap(nextMoves[i], nextMoves[j]);
            }
        }
    }

    // try candidate moves
    for (int i = 0; i < numCandidates; i++) {
        int moveIdx = nextMoves[i];
        int nx = x + dx[moveIdx];
        int ny = y + dy[moveIdx];

        if (solveKnightTour(nx, ny, moveNumber + 1, n, board)) {
            return true;
        }
    }

    // backtrack if no move succeeds
    board[x][y] = -1;
    return false;
}

// display chessboard
void printBoard(int board[][MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(4) << board[i][j];
        }
        cout << endl;
    }
}

// run one test tour
void runTour(int n, int startX, int startY) {
    cout << "==========================================" << endl;
    cout << " Knight's Tour for " << n << "x" << n 
         << " Board from (" << startX << ", " << startY << ")" << endl;
    cout << "==========================================" << endl;

    int board[MAX_N][MAX_N];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) board[i][j] = -1;
    }

    if (solveKnightTour(startX, startY, 1, n, board)) {
        cout << "Tour successfully found:" << endl;
        printBoard(board, n);
    } else {
        cout << "No valid knight's tour exists for this configuration." << endl;
    }
    cout << endl;
}

int main() {
    cout << "==========================================" << endl;
    cout << " TASK 4: KNIGHT'S TOUR USING BACKTRACKING" << endl;
    cout << "==========================================" << endl;

    // test 5x5 board
    runTour(5, 0, 0);

    // test 8x8 board
    runTour(8, 0, 0);

    return 0;
}
