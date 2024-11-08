#pragma once
#include "domain_CheckersJNI.h"
#include "Board.cpp"
#include <cmath>
#include "SelectedCell.cpp"
#include "Piece.cpp"
#include "DefaultPiece.cpp"
#include "KingPiece.cpp"
#include "FromToCoordinates.cpp"

SelectedCell cell = SelectedCell();
FromToCoordinates ftc = FromToCoordinates();
Board board = Board();

JNIEXPORT jintArray JNICALL Java_domain_CheckersJNI_getBoardState(JNIEnv *env, jobject obj) {
    jintArray result = env->NewIntArray(8 * 8);

    const int *boardState = board.getBoardState();

    env->SetIntArrayRegion(result, 0, 64, boardState);

    return result;
}

JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getSelectedCol(JNIEnv *, jobject){return cell.getCol();}

JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getSelectedRow(JNIEnv *, jobject){return cell.getRow();}

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setSelectedCol(JNIEnv *, jobject, jint a){cell.setCol(a);}

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setSelectedRow (JNIEnv *, jobject, jint a){cell.setRow(a);}

JNIEXPORT jboolean JNICALL Java_domain_CheckersJNI_isCellSelected (JNIEnv *, jobject){return cell.isCellSelected();}

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setCellSelected (JNIEnv *, jobject, jboolean a){cell.setCellSelected(a);}



JNIEXPORT void JNICALL Java_domain_CheckersJNI_setFromRow(JNIEnv *, jobject, jint a){ftc.fromRow = a;}

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setFromCol(JNIEnv *, jobject, jint a){ftc.fromCol = a;}

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setToCol(JNIEnv *, jobject, jint a){ftc.toCol = a;}

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setToRow(JNIEnv *, jobject, jint a){ftc.toRow = a;}



JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getFromRow(JNIEnv *, jobject){return ftc.fromRow;}

JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getFromCol(JNIEnv *, jobject){return ftc.fromCol;}

JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getToCol(JNIEnv *, jobject){return ftc.toCol;}

JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getToRow(JNIEnv *, jobject){return ftc.toRow;}


JNIEXPORT void JNICALL Java_domain_CheckersJNI_setBoardValue(JNIEnv *, jobject, jint x, jint y, jint val){board.boardState[x][y] = val;}

JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getBoardSize(JNIEnv *env, jobject obj) { return board.size; }

JNIEXPORT jboolean JNICALL Java_domain_CheckersJNI_getCurrentPlayer(JNIEnv *env, jobject obj) { return board.isBlackTurn; }

JNIEXPORT void JNICALL Java_domain_CheckersJNI_setCurrentPlayer(JNIEnv *env, jobject obj, jboolean a) {board.isBlackTurn = a;}

JNIEXPORT jint JNICALL Java_domain_CheckersJNI_getBoardValue (JNIEnv *, jobject, jint x, jint y){return board.boardState[x][y];}

JNIEXPORT jboolean JNICALL Java_domain_CheckersJNI_gameFinished(JNIEnv *, jobject){

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

JNIEXPORT void JNICALL Java_domain_CheckersJNI_resetGame(JNIEnv *, jobject){
    board.initializeBoard();
    board.isBlackTurn = false;
    cell.setCellSelected(false);
    cell.setRow(-1);
    cell.setCol(-1);
    ftc.toRow = -1;
    ftc.fromRow = -1;
    ftc.toCol = -1;
    ftc.fromCol = -1;
}


// Проверка обязательного захвата для текущего игрока

JNIEXPORT jboolean JNICALL Java_domain_CheckersJNI_movePiece(JNIEnv *env, jobject obj, jint fromX, jint fromY, jint toX, jint toY) {
    // Check if destination cell is empty
    if (board.boardState[toX][toY] != 0) return false;

    int pieceValue = board.boardState[fromX][fromY];
    int player = (pieceValue == 1 || pieceValue == 3) ? 1 : 2;
    bool isKing = pieceValue >= 3;

    // Check if it's the current player's turn
    if ((player == 1 && !board.isBlackTurn) || (player == 2 && board.isBlackTurn)) {return false;}  // Not this player's turn

    Piece *piece = isKing ? static_cast<Piece*>(new KingPiece(player, fromX, fromY))
                          : static_cast<Piece*>(new DefaultPiece(player, fromX, fromY));


    // Check if capture is mandatory
    bool captureObligatory = piece -> mustCapture(player, board);
    bool beatedOnce = false;

    bool moveSuccessful = false;

    // Logic for kings
    if (isKing) {
        if (piece->canMove(toX, toY)) {  // Ensure it's a diagonal move
            int captureCount = 0;

            if (!static_cast<KingPiece*>(piece)->hasCapturePath(toX, toY, captureCount, board)) return false; //invalid toX and toY positions. Move cancelled

            if (captureObligatory && captureCount == 0) return false;  // Must capture if possible

            if (captureCount > 0) {                               //if found smthing
                if (piece->moveAndCapture(toX, toY, board)){      //move to destination and eat opponent pieces
                    moveSuccessful = true;
                    beatedOnce = true;                            //flag for continuing move if there are another pieces that must be eaten
                }

            } else {
                if (!captureObligatory) {  // Allow non-capturing moves only if capture is not mandatory
                    piece->move(toX, toY, board);
                    moveSuccessful = true;
                }
            }
        }
    }
        // Logic for regular pieces with forward and backward capture capability
    else {
        if (piece->canMove(toX, toY)) {
            if (!captureObligatory) {  // Allow non-capturing moves only if capture is not mandatory
                piece->move(toX, toY, board);
                moveSuccessful = true;
            }
        } else if (piece->canCapture(toX, toY)) {
            if (piece->moveAndCapture(toX, toY, board)){
                moveSuccessful = true;
                beatedOnce = true;
            }
        }
    }

    // Check if piece should be promoted to king
    if (moveSuccessful) {
        if ((player == 1 && toX == 7) || (player == 2 && toX == 0)) {
            if (piece->getValue() < 3)
                board.boardState[toX][toY] += 2;  // Promote to king if not a king yet
        }

        // Проверка на возможность дальнейшего захвата
        if (piece->canCaptureFrom(toX, toY, board) && beatedOnce) {
            return true;  // Очередь не меняется, игрок продолжает ход
        } else {
            board.isBlackTurn = !board.isBlackTurn;
        }
    }

    return moveSuccessful;
}