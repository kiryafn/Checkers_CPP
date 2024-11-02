#pragma once
class SelectedCell {
private:
    int row = -1;
    int col = -1;
    bool cellSelected = false;
public:
    int getRow() { return row; }

    void setRow(int a) { row = a; }

    int getCol() { return col; }

    void setCol(int a) {col = a; }

    bool isCellSelected() { return cellSelected; }

    void setCellSelected(bool a) { cellSelected = a; }
};
