#include "cmath"

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

    void beatOpponentPieceByDiagonal(int fromX, int fromY, int toX, int toY, int player, int piece, bool& moveSuccessful){
        // Capture move (diagonal two-cell jump)
            int midX = (fromX + toX) / 2;
            int midY = (fromY + toY) / 2;
            int opponentPiece = (player == 1) ? 2 : 1;
            int opponentKing = opponentPiece + 2;

            // Check if capture conditions are met
            if (boardState[midX][midY] == opponentPiece || boardState[midX][midY] == opponentKing) {
                // Capture opponent piece
                boardState[toX][toY] = piece;
                boardState[fromX][fromY] = 0;
                boardState[midX][midY] = 0;  // Remove captured piece
                moveSuccessful = true;
            }
    }


};