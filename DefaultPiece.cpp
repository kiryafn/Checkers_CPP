#pragma once
#include "Piece.cpp"
#include <cmath>

class DefaultPiece : public Piece {
public:
    DefaultPiece(int player, int x, int y) : Piece(player, x, y) {
        value = player;
    }

    bool canMove(int toX, int toY) override {
        int direction = (player == 1) ? 1 : -1;
        return (abs(toX - posX) == 1 && abs(toY - posY) == 1 && (toX - posX == direction));
    }

    bool canCapture(int toX, int toY) override {
        return (abs(toX - posX) == 2 && abs(toY - posY) == 2);
    }

    bool moveAndCapture(int toX, int toY, Board& board) override{
        int midX = (posX + toX) / 2;
        int midY = (posY + toY) / 2;

        int opponentPiece = (player == 1) ? 2 : 1;
        int opponentKing = (player == 1) ? 4 : 3;

        if (board.boardState[midX][midY] == opponentPiece || board.boardState[midX][midY] == opponentKing) { //If we jump over opponents piece
            move(toX, toY, board);
            board.boardState[midX][midY] = 0;
            return true;
        }
        else return false;
    };


};