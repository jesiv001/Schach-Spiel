//
// Created by Jenush on 15.07.2025.
//

#ifndef SCHACH_QT_POS_H
#define SCHACH_QT_POS_H


class Pos {
private:
    int _col = -1;
    int _row = -1;

public:
    Pos();
    Pos(int col, int row);
    void set(int col, int row);
    [[nodiscard]] int get_col() const;
    [[nodiscard]] int get_row() const;
    bool operator==(Pos &other) const;
};


#endif //SCHACH_QT_POS_H
