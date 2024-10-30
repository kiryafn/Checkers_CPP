#pragma once
#include "Board.cpp"

class Piece {
protected:
    int player;   // 1 - Black, 2 - White
    int posX, posY;
    int value;

public:
    Piece(int player, int x, int y) : player(player), posX(x), posY(y){}

    virtual bool canMove(int toX, int toY) = 0;
    virtual bool canCapture(int toX, int toY) = 0;

    void move(int toX, int toY, Board& board){
        board.boardState[toX][toY] = value;
        board.boardState[posX][posY] = 0;
    };
    virtual bool moveAndCapture(int toX, int toY, Board& board) = 0;

    int getPlayer() const { return player; }
    int getX() const { return posX; }
    int getY() const { return posY; }
    int getValue() const { return value; }

    bool canCaptureFrom(int x, int y, Board& board) {
        int piece = board.boardState[x][y];
        if (piece == 0) return false;

        int player = (piece == 1 || piece == 3) ? 1 : 2;
        int opponentPiece = (player == 1) ? 2 : 1;
        int opponentKing = opponentPiece + 2;

        // Проверка всех направлений на возможность захвата
        for (int dx = -2; dx <= 2; dx += 4) {
            for (int dy = -2; dy <= 2; dy += 4) {
                int midX = x + dx / 2;
                int midY = y + dy / 2;
                int toX = x + dx;
                int toY = y + dy;

                if (toX >= 0 && toX < 8 && toY >= 0 && toY < 8 &&
                    board.boardState[toX][toY] == 0 &&  // Конечная клетка пуста
                    (board.boardState[midX][midY] == opponentPiece || board.boardState[midX][midY] == opponentKing)) {
                    return true;  // Есть возможность захвата
                }
            }
        }
        return false;
    }

    bool mustCapture(int player, Board& board) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if ((player == 1 && (board.boardState[i][j] == 1 || board.boardState[i][j] == 3)) ||
                    (player == 2 && (board.boardState[i][j] == 2 || board.boardState[i][j] == 4))) {
                    if (canCaptureFrom(i, j, board)) return true;
                }
            }
        }
        return false;
    }


};