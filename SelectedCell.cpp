#pragma once
class SelectedCell {
private:
    int selectedRow = -1;
    int selectedCol = -1;
    bool pieceSelected = false;
public:
    int getSelectedRow() { return selectedRow; }

    void setSelectedRow(int a) { selectedRow = a; }

    int getSelectedCol() { return selectedCol; }

    void setSelectedCol(int a) {selectedCol = a; }

    bool isPieceSelected() { return pieceSelected; }

    void setPieceSelected(bool a) { pieceSelected = a; }
};
