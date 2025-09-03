#ifndef SCHACH_QT_PIECE_H
#define SCHACH_QT_PIECE_H

#include "pos.h"
#include <vector>
#include <map>
#include "gameconstants.h"
//die helper funktionen können keinen referenz von board bekoomen da ich bei der map ein derefernzierungsopoerator nutze in der Funktion
class Piece {
private:
    [[nodiscard]] virtual std::vector<Pos>
    possible_moves_helper( std::map<std::pair<int, int>, char> current_board,
                          char color_first_letter,
                          char color_last_letter) const = 0;

public:
    char _piece_name;
    char _piece_color;
    Pos _pos;

    Piece(char name, char color, int col, int row);
    void move(int col, int row);

    [[nodiscard]] virtual std::vector<Pos>
    possible_move( std::map<std::pair<int, int>, char>& current_board) const = 0;

    virtual ~Piece() = default;
};

// --------------------------------------------------------------

class King : public Piece {
private:
    [[nodiscard]] std::vector<Pos>
    possible_moves_helper( std::map<std::pair<int, int>, char> current_board,
                          char color_first_letter,
                          char color_last_letter) const override;

public:
    King(char name, char color, int col, int row);

    [[nodiscard]] std::vector<Pos>
    possible_move( std::map<std::pair<int, int>, char>& current_board) const override;
};

// --------------------------------------------------------------

class Pawn : public Piece {
private:
    [[nodiscard]] std::vector<Pos>
    possible_moves_helper( std::map<std::pair<int, int>, char> current_board,
                          char color_first_letter,
                          char color_last_letter) const override;

public:
    Pawn(char name, char color, int col, int row);

    [[nodiscard]] std::vector<Pos>
    possible_move( std::map<std::pair<int, int>, char> &current_board) const override;

};

// --------------------------------------------------------------

class Bishop : public Piece {
private:
    [[nodiscard]] std::vector<Pos>
    possible_moves_helper( std::map<std::pair<int, int>, char> current_board,
                          char color_first_letter,
                          char color_last_letter) const override;

public:
    Bishop(char name, char color, int col, int row);

    [[nodiscard]] std::vector<Pos>
    possible_move( std::map<std::pair<int, int>, char>& current_board) const override;
};

// --------------------------------------------------------------

class Knight : public Piece {
private:
    [[nodiscard]] std::vector<Pos>
    possible_moves_helper( std::map<std::pair<int, int>, char> current_board,
                          char color_first_letter,
                          char color_last_letter) const override;

public:
    Knight(char name, char color, int col, int row);

    [[nodiscard]] std::vector<Pos>
    possible_move( std::map<std::pair<int, int>, char> &current_board) const override;
};

// --------------------------------------------------------------

class Rook : public Piece {
private:
    [[nodiscard]] std::vector<Pos>
    possible_moves_helper( std::map<std::pair<int, int>, char> current_board,
                          char color_first_letter,
                          char color_last_letter) const override;

public:
    Rook(char name, char color, int col, int row);

    [[nodiscard]] std::vector<Pos>
    possible_move( std::map<std::pair<int, int>, char>& current_board) const override;
};

// --------------------------------------------------------------

class Queen : public Piece {
private:
    [[nodiscard]] std::vector<Pos>
    possible_moves_helper( std::map<std::pair<int, int>, char> current_board,
                          char color_first_letter,
                          char color_last_letter) const override;

public:
    Queen(char name, char color, int col, int row);

    [[nodiscard]] std::vector<Pos>
    possible_move( std::map<std::pair<int, int>, char>& current_board) const override;
};

#endif //SCHACH_QT_PIECE_H
