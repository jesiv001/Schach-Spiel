//
// Created by Jenush on 06.06.2025.
//

#ifndef SCHACH_QT_GAMEBOARD_H
#define SCHACH_QT_GAMEBOARD_H



#include <string>
#include <vector>
#include <array>
#include <map>
#include "piece.h"
#include "gameconstants.h"


class GameBoard {

private:
    int _turn = 0;
    std::vector<std::map<std::pair<int, int>, char>> _board_history;
    std::vector<Piece *> _pieces;
    [[maybe_unused]]void print_gameboard();//war zum debuggen hilfreich
    Piece *
    capture_piece(int col, int row);//um das deleted piece zurück zu geben,wenn der Zug gegebenenfalls nicht legal war
    [[nodiscard]] bool is_check(char color);
    void check_castling(std::vector<Pos> &castling_moves);
    void check_en_passant(std::vector<Pos> &en_passant_moves, int pawn_col, int pawn_row);
    [[nodiscard]] std::string draw_50_moves();
    [[nodiscard]] std::string draw_few_material();
    [[nodiscard]] std::string draw_repetition();
    [[nodiscard]] std::string check_stalemate_win();


public:
    static const int SIZE = 8; //da es auf das board bezogen ist hab ich es nicht in gameconstants rein gemacht
    std::map<std::pair<int, int>, char> _current_board;
    std::string _message;
    bool _promotion = false;
    GameBoard();
    ~GameBoard();
    std::vector<Pos> check_pawn_promotion();
    [[nodiscard]] char check_turn() const;
    [[nodiscard]] std::vector<Pos> get_possible_moves(int col, int row);
    void set_cell(int colbefore, int rowbefore, int col, int row);
    std::string check_game_state();
    void reset();
    void setup_start_position();


};


#endif //SCHACH_QT_GAMEBOARD_H
