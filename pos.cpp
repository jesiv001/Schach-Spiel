//
// Created by Jenush on 15.07.2025.
//

#include "pos.h"


Pos::Pos(int col, int row) {
    _col = col;
    _row = row;
}


Pos::Pos() : _col(-1), _row(-1) {}


void Pos::set(int col, int row) {
    _col = col;
    _row = row;
}


int Pos::get_col() const {
    return _col;
}


int Pos::get_row() const {
    return _row;
}


bool Pos::operator==(Pos &other) const {
    return _col == other.get_col() && _row == other.get_row();
}