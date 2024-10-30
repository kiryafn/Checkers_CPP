#pragma once
#include "Board.cpp"

class MovePiece {
public:
    static bool movePiece(Board& board, int fromX, int fromY, int toX, int toY, int piece) {
        board.boardState[toX][toY] = piece;
        board.boardState[fromX][fromY] = 0;
    }

    static bool movePiece(Board& board, int fromX, int fromY, int toX, int toY, int midX, int midY, int piece) {
        board.boardState[toX][toY] = piece;
        board.boardState[fromX][fromY] = 0;
        board.boardState[midX][midY] = 0;
    }

    static bool moveAcrossDiagonalAndCheckNumberOfOpponentPieces(Board& board, int fromX, int fromY, int toX, int toY, int opponentPiece, int opponentKing, bool& captured, int& captureCount){
        int dx = (toX > fromX) ? 1 : -1;
        int dy = (toY > fromY) ? 1 : -1;
        int x = fromX + dx;
        int y = fromY + dy;

        // Traverse cells along the diagonal
        while (x != toX && y != toY) {
            if (board.boardState[x][y] != 0) {

                // Check if the piece is an opponent piece
                if (board.boardState[x][y] == opponentPiece || board.boardState[x][y] == opponentKing) {
                    if (captured) {
                        // If already captured a piece on this path, can't capture more without a gap
                        return false;
                    }
                    captured = true;
                    captureCount++;
                } else {
                    // Encountered a piece of the same player, invalid move
                    return false;
                }
            } else if (captured) {
                // Found an empty cell after capturing an opponent piece; allow continued movement
                captured = false;
            }

            x += dx;
            y += dy;
        }
    }
};
