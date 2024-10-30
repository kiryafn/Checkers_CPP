#pragma once
class Board{
public:
    int size = 8;
    int boardState[8][8];
    bool isBlackTurn = false;
public: Board(){

        initializeBoard();
    }

    void initializeBoard() {
        for (int row=0; row<8; ++row) {
            for (int col = 0; col < 8; ++col) {

                if (row < 3 && (row + col) % 2 == 1)
                    boardState[row][col] = 1; //!Player 1 pieces BLACK
                else if (row > 4 && (row + col) % 2 == 1)
                    boardState[row][col] = 2; //!Player 2 pieces WHITE
                else
                    boardState[row][col] = 0; //!Empty slots
            }
        }
    }

    const int* getBoardState() const {
        return &boardState[0][0]; //! Returns pointer to the beginning of the array
    }

};