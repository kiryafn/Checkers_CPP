#include "CheckersJNI.h"
#include "Board.cpp"
#include <cmath>
#include "SelectedCell.cpp"

SelectedCell selectedCell = SelectedCell();
Board board = Board();

JNIEXPORT jintArray JNICALL Java_CheckersJNI_getBoardState(JNIEnv *env, jobject obj) {
    jintArray result = env->NewIntArray(8 * 8);

    const int *boardState = board.getBoardState();

    env->SetIntArrayRegion(result, 0, 64, boardState);

    return result;
}

JNIEXPORT jint JNICALL Java_CheckersJNI_getSelectedCol (JNIEnv *, jobject){return selectedCell.getSelectedCol();}

JNIEXPORT jint JNICALL Java_CheckersJNI_getSelectedRow (JNIEnv *, jobject){return  selectedCell.getSelectedRow();}

JNIEXPORT void JNICALL Java_CheckersJNI_setSelectedCol (JNIEnv *, jobject, jint a){selectedCell.setSelectedCol(a);}

JNIEXPORT void JNICALL Java_CheckersJNI_setSelectedRow (JNIEnv *, jobject, jint a){selectedCell.setSelectedRow(a);}

JNIEXPORT jboolean JNICALL Java_CheckersJNI_isPieceSelected(JNIEnv *, jobject){return selectedCell.isPieceSelected();}

JNIEXPORT void JNICALL Java_CheckersJNI_setPieceSelected (JNIEnv *, jobject, jboolean a){selectedCell.setPieceSelected(a);}

JNIEXPORT jint JNICALL Java_CheckersJNI_getBoardSize(JNIEnv *env, jobject obj) { return board.size; }

JNIEXPORT jboolean JNICALL Java_CheckersJNI_getCurrentPlayer(JNIEnv *env, jobject obj) { return board.isBlackTurn; }

JNIEXPORT jint JNICALL Java_CheckersJNI_getBoardValue (JNIEnv *, jobject, jint x, jint y){return board.boardState[x][y];}

JNIEXPORT jboolean JNICALL Java_CheckersJNI_gameFinished(JNIEnv *, jobject){
        bool player1HasPieces = false;
        bool player2HasPieces = false;

        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if (board.boardState[row][col] == 1 || board.boardState[row][col] == 3) {
                    player1HasPieces = true;
                }
                if (board.boardState[row][col] == 2 || board.boardState[row][col] == 4) {
                    player2HasPieces = true;
                }
            }
        }

        // Если у одного из игроков больше нет фишек, игра окончена
        return !(player1HasPieces && player2HasPieces);
}

bool canCaptureFrom(int x, int y) {
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

// Проверка обязательного захвата для текущего игрока
bool mustCapture(int player) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((player == 1 && (board.boardState[i][j] == 1 || board.boardState[i][j] == 3)) ||
                (player == 2 && (board.boardState[i][j] == 2 || board.boardState[i][j] == 4))) {
                if (canCaptureFrom(i, j)) return true;
            }
        }
    }
    return false;
}

JNIEXPORT jboolean JNICALL
Java_CheckersJNI_movePiece(JNIEnv *env, jobject obj, jint fromX, jint fromY, jint toX, jint toY) {
    // Check if destination cell is empty
    if (board.boardState[toX][toY] != 0) return false;

    int piece = board.boardState[fromX][fromY];
    int player = (piece == 1 || piece == 3) ? 1 : 2;
    int direction = (player == 1) ? 1 : -1;  // Направление хода: вниз для игрока 1, вверх для игрока 2

    int opponentPiece = (player == 1) ? 2 : 1;
    int opponentKing = opponentPiece + 2;

    // Check if it's the current player's turn
    if ((player == 1 && !board.isBlackTurn) || (player == 2 && board.isBlackTurn)) {
        return false;  // Not this player's turn
    }

    // Check if capture is mandatory
    bool captureObligatory = mustCapture(player);
    bool beatedOnce = false;

    bool moveSuccessful = false;
    bool isKing = (piece == 3 || piece == 4);

    // Logic for kings
    if (isKing) {
        if (abs(toX - fromX) == abs(toY - fromY)) {  // Ensure it's a diagonal move
            int dx = (toX > fromX) ? 1 : -1;
            int dy = (toY > fromY) ? 1 : -1;
            int x = fromX + dx;
            int y = fromY + dy;
            bool captured = false;
            int captureCount = 0;

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

            if (captureObligatory && captureCount == 0) return false;  // Must capture if possible
            if (captureCount > 0) {
                x = fromX + dx;
                y = fromY + dy;
                while (x != toX && y != toY) {
                    if (board.boardState[x][y] != 0) board.boardState[x][y] = 0;
                    x += dx;
                    y += dy;
                }
                board.boardState[toX][toY] = piece;
                board.boardState[fromX][fromY] = 0;
                moveSuccessful = true;
            } else {
                if (!captureObligatory) {  // Allow non-capturing moves only if capture is not mandatory
                    board.boardState[toX][toY] = piece;
                    board.boardState[fromX][fromY] = 0;
                    moveSuccessful = true;
                }
            }
        }
    }
        // Logic for regular pieces with forward and backward capture capability
    else {
        if (abs(toX - fromX) == 1 && abs(toY - fromY) == 1 && toX - fromX == direction) {
            if (!captureObligatory) {  // Allow non-capturing moves only if capture is not mandatory
                board.boardState[toX][toY] = piece;
                board.boardState[fromX][fromY] = 0;
                moveSuccessful = true;
            }
        } else if (abs(toX - fromX) == 2 && abs(toY - fromY) == 2) {
            int midX = (fromX + toX) / 2;
            int midY = (fromY + toY) / 2;

            if (board.boardState[midX][midY] == opponentPiece || board.boardState[midX][midY] == opponentKing) {
                board.boardState[toX][toY] = piece;
                board.boardState[fromX][fromY] = 0;
                board.boardState[midX][midY] = 0;
                moveSuccessful = true;
                beatedOnce = true;

            }
        }
    }

    // Check if piece should be promoted to king
    if (moveSuccessful) {
        if ((player == 1 && toX == 7) || (player == 2 && toX == 0)) {
            if (board.boardState[toX][toY] < 3)
                board.boardState[toX][toY] += 2;  // Promote to king
        }

        // Проверка на возможность дальнейшего захвата
        if (canCaptureFrom(toX, toY) && beatedOnce) {
            return true;  // Очередь не меняется, игрок продолжает ход
        } else {
            board.isBlackTurn = !board.isBlackTurn;
        }
    }

    return moveSuccessful;
}