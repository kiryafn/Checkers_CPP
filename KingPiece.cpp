#pragma once
#include "Piece.cpp"
#include "Board.cpp"
#include <cmath>

class KingPiece : public Piece {
public:
    KingPiece(int player, int x, int y) : Piece(player, x, y) {
        value = player + 2;
    }

    bool canMove(int toX, int toY) override {
        return abs(toX - posX) == abs(toY - posY);  // Diagonal move for any distance
    }

    bool canCapture(int toX, int toY) override {
        return canMove(toX, toY);  // Allow diagonal move, checking capture logic separately
    }

    bool hasCapturePath(int toX, int toY, int &captureCount, Board &board) {
        int directionX = (toX > posX) ? 1 : -1;
        int directionY = (toY > posY) ? 1 : -1;

        int opponentPiece = (player == 1) ? 2 : 1;
        int opponentKing = (player == 1) ? 4 : 3;

        bool captured = false;

        //Coordinates of every checked cell before we reach (toX, toY)
        int x = posX + directionX;
        int y = posY + directionY;

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

            x += directionX;
            y += directionY;
        }
        return true;
    }
    bool moveAndCapture(int toX, int toY, Board& board){
        int directionX = (toX > posX) ? 1 : -1;
        int directionY = (toY > posY) ? 1 : -1;

        int x = posX + directionX;
        int y = posY + directionY;

        bool beatedOnce = false;

        while (x != toX && y != toY) {

            if (board.boardState[x][y] != 0) {
                board.boardState[x][y] = 0;
                beatedOnce = true;
            }

            x += directionX;
            y += directionY;
        }

        move(toX, toY, board);
        return beatedOnce;
    }
};