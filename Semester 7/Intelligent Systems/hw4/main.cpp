#include <iostream>
#include <vector>
#include <climits>

const int BOARD_SIZE = 3;
const char EMPTY_SYMBOL = '-';
char computerSymbol;
char playerSymbol;
int steps = 0;
char board[BOARD_SIZE][BOARD_SIZE] = {{EMPTY_SYMBOL, EMPTY_SYMBOL, EMPTY_SYMBOL},
                                      {EMPTY_SYMBOL, EMPTY_SYMBOL, EMPTY_SYMBOL},
                                      {EMPTY_SYMBOL, EMPTY_SYMBOL, EMPTY_SYMBOL}};


void printBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool gameOver() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if ((board[i][0] != EMPTY_SYMBOL) && (board[i][0] == board[i][1]) && (board[i][0] == board[i][2])) {
            return true;
        }
        if ((board[0][i] != EMPTY_SYMBOL) && (board[0][i] == board[1][i]) && (board[0][i] == board[2][i])) {
            return true;
        }
    }
    if ((board[0][0] != EMPTY_SYMBOL) && (board[0][0] == board[1][1]) && (board[0][0] == board[2][2])) {
        return true;
    }
    if ((board[0][2] != EMPTY_SYMBOL) && (board[0][2] == board[1][1]) && (board[0][2] == board[2][0])) {
        return true;
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == EMPTY_SYMBOL) {
                return false;
            }
        }
    }
    return true;
}

int evaluate(int depth) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if ((board[i][0] != EMPTY_SYMBOL) && (board[i][0] == board[i][1]) && (board[i][0] == board[i][2])) {
            if (board[i][0] == computerSymbol) {
                return 10 - depth;
            } else {
                return depth - 10;
            }
        }
        if ((board[0][i] != EMPTY_SYMBOL) && (board[0][i] == board[1][i]) && (board[0][i] == board[2][i])) {
            if (board[0][i] == computerSymbol) {
                return 10 - depth;
            } else {
                return depth - 10;
            }
        }
    }
    if ((board[0][0] != EMPTY_SYMBOL) && (board[0][0] == board[1][1]) && (board[0][0] == board[2][2])) {
        if (board[0][0] == computerSymbol) {
            return 10 - depth;
        } else {
            return depth - 10;
        }
    }
    if ((board[0][2] != EMPTY_SYMBOL) && (board[0][2] == board[1][1]) && (board[0][2] == board[2][0])) {
        if (board[0][2] == computerSymbol) {
            return 10 - depth;
        } else {
            return depth - 10;
        }
    }
    return 0;
}

int minimax(int depth, int alpha, int beta, bool isMaximizer) {
    int score = evaluate(depth);

    if (score > 0 || score < 0 || gameOver()) {
        return score;
    }

    if (isMaximizer) {
        int best = INT_MIN;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == EMPTY_SYMBOL) {
                    board[i][j] = computerSymbol;
                    best = std::max(best, minimax(depth + 1, alpha, beta, false));
                    alpha = std::max(alpha, best);
                    board[i][j] = EMPTY_SYMBOL;
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == EMPTY_SYMBOL) {
                    board[i][j] = playerSymbol;
                    best = std::min(best, minimax(depth + 1, alpha, beta, true));
                    beta = std::min(beta, best);
                    board[i][j] = EMPTY_SYMBOL;
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return best;
    }
}

void makeBestMove() {
    int bestVal = INT_MIN;
    int bestMoveRow = -1;
    int bestMoveCol = -1;
    int alpha = INT_MIN;
    int beta = INT_MAX;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == EMPTY_SYMBOL) {
                board[i][j] = computerSymbol;
                int moveVal = minimax(0, alpha, beta, false);
                board[i][j] = EMPTY_SYMBOL;

                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    bestMoveRow = i;
                    bestMoveCol = j;
                }
            }
        }
    }

    board[bestMoveRow][bestMoveCol] = computerSymbol;
}

int main(int argc, char *argv[]) {
    bool playerTurn = (argc > 1);
    playerSymbol = 'X';
    computerSymbol = 'O';

    if (!playerTurn) {
        computerSymbol = 'X';
        playerSymbol = 'O';
        makeBestMove();
        steps++;
        printBoard();
    }

    while (!gameOver()) {
        int row, col;
        do {
            std::cin >> row >> col;
            row--;
            col--;
        } while (row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE || board[row][col] != EMPTY_SYMBOL);
        board[row][col] = playerSymbol;
        steps++;

        if (gameOver()) {
            break;
        }

        makeBestMove();
        steps++;
        printBoard();
    }

    int result = evaluate(steps);
    if (result > 0) {
        std::cout << "Computer wins!" << std::endl;
    } else if (result < 0) {
        std::cout << "Player wins!" << std::endl;
    } else {
        std::cout << "Tie!" << std::endl;
    }

    return 0;
}
