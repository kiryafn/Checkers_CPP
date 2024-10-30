#include <cmath>
#pragma once
class MoveValidator {
public:
    static bool isDiagonalMove(int fromX, int fromY, int toX, int toY) {
        return abs(toX - fromX) == abs(toY - fromY);
    }

    static bool isValidOneStepMove(int fromX, int fromY, int toX, int toY, int direction) {
        return abs(toX - fromX) == 1 && abs(toY - fromY) == 1 && (toX - fromX == direction);
    }
};
