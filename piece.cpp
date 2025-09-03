//
// Created by Jenush on 15.07.2025.
//

#include "piece.h"
/////////////////////////////////////Piece//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Piece::Piece(char name, char color, int col, int row) {
    _piece_name = name;
    _piece_color = color;
    _pos.set(col, row);
}


void Piece::move(int col, int row) {
    _pos.set(col, row);
}

/////////////////////////////////////Piece-Ende//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////Pawn//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Pawn::Pawn(char name, char color, int col, int row) : Piece(name, color, col, row) {}


std::vector<Pos> Pawn::possible_moves_helper(std::map<std::pair<int, int>, char> current_board,
                                             char enemy_first_letter,
                                             char enemy_last_letter) const {
    std::vector<Pos> moves;
    int col = _pos.get_col();
    int row = _pos.get_row();

    if ( _piece_color == 'w' ) {
        // Angriff oben links
        if ( current_board[{col - 1, row + 1}] != CHESS::EMPTYSPACE &&
             current_board[{col - 1, row + 1}] >= enemy_first_letter &&
             current_board[{col - 1, row + 1}] <= enemy_last_letter ) {
            moves.emplace_back(col - 1, row + 1);
        }
        // Angriff oben rechts
        if ( current_board[{col + 1, row + 1}] != CHESS::EMPTYSPACE &&
             current_board[{col + 1, row + 1}] >= enemy_first_letter &&
             current_board[{col + 1, row + 1}] <= enemy_last_letter ) {
            moves.emplace_back(col + 1, row + 1);
        }
        // Ein Feld nach vorne (frei)
        if ( current_board[{col, row + 1}] == CHESS::EMPTYSPACE ) {
            moves.emplace_back(col, row + 1);
            // Anfangszug zwei Felder vor, wenn beide frei
            if ( row == 2 && current_board[{col, row + 2}] == CHESS::EMPTYSPACE ) {
                moves.emplace_back(col, row + 2);
            }
        }

    } else if ( _piece_color == 'b' ) {
        // Angriff unten links
        if ( current_board[{col - 1, row - 1}] != CHESS::EMPTYSPACE &&
             current_board[{col - 1, row - 1}] >= enemy_first_letter &&
             current_board[{col - 1, row - 1}] <= enemy_last_letter ) {
            moves.emplace_back(col - 1, row - 1);
        }
        // Angriff unten rechts
        if ( current_board[{col + 1, row - 1}] != CHESS::EMPTYSPACE &&
             current_board[{col + 1, row - 1}] >= enemy_first_letter &&
             current_board[{col + 1, row - 1}] <= enemy_last_letter ) {
            moves.emplace_back(col + 1, row - 1);
        }
        // Ein Feld nach vorne
        if ( current_board[{col, row - 1}] == CHESS::EMPTYSPACE ) {
            moves.emplace_back(col, row - 1);
            //
            if ( row == 7 && current_board[{col, row - 2}] == CHESS::EMPTYSPACE ) {
                moves.emplace_back(col, row - 2);
            }
        }

    }

    return moves;
}


std::vector<Pos> Pawn::possible_move(std::map<std::pair<int, int>, char> &current_board) const {
    if ( _piece_color == 'w' ) {
        return possible_moves_helper(current_board, CHESS::BLACKPIECE[0],
                                     CHESS::BLACKPIECE[1]); // Gegner: schwarze Figuren Kleinbuchstaben
    } else {
        return possible_moves_helper(current_board, CHESS::WHITEPIECE[0],
                                     CHESS::WHITEPIECE[1]); // Gegner: weiße Figuren Großbuchstaben
    }
}

/////////////////////////////////////Pawn-Ende//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








/////////////////////////////////////Rook//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Rook::Rook(char name, char color, int col, int row) : Piece(name, color, col, row) {

}


std::vector<Pos> Rook::possible_moves_helper(std::map<std::pair<int, int>, char> current_board, char enemy_first_letter,
                                             char enemy_last_letter) const {
    //nach oben
    std::vector<Pos> moves;
    int rook_pos_col = _pos.get_col();
    for ( int i = _pos.get_row() + 1; i <= CHESS::ROWMAX; i++ ) {

        if ( current_board[{rook_pos_col, i}] == CHESS::EMPTYSPACE ) {
            moves.emplace_back(rook_pos_col, i);
        } else if ( current_board[{rook_pos_col, i}] >= enemy_first_letter &&
                    current_board[{rook_pos_col, i}] <= enemy_last_letter ) {
            moves.emplace_back(rook_pos_col, i);
            //schwarze figur schlagen
            break;
        } else
            break;
    }

    //nach unten

    for ( int i = _pos.get_row() - 1; i >= CHESS::ROWMIN; i-- ) {

        if ( current_board[{rook_pos_col, i}] == CHESS::EMPTYSPACE ) {
            moves.emplace_back(rook_pos_col, i);
        } else if ( current_board[{rook_pos_col, i}] >= enemy_first_letter &&
                    current_board[{rook_pos_col, i}] <= enemy_last_letter ) {
            moves.emplace_back(rook_pos_col, i);

            break;
        } else
            break;
    }

    //nach rechts
    int rook_pos_row = _pos.get_row();
    for ( int i = _pos.get_col() + 1; i <= CHESS::COLMAX; i++ ) {

        if ( current_board[{i, rook_pos_row}] == CHESS::EMPTYSPACE ) {
            moves.emplace_back(i, rook_pos_row);
        } else if ( current_board[{i, rook_pos_row}] >= enemy_first_letter &&
                    current_board[{i, rook_pos_row}] <= enemy_last_letter ) {
            moves.emplace_back(i, rook_pos_row);
            //gegnerische figur schlagen
            break;
        } else
            break;
    }

    //nach links
    for ( int i = _pos.get_col() - 1; i >= 1; i-- ) {

        if ( current_board[{i, rook_pos_row}] == CHESS::EMPTYSPACE ) {
            moves.emplace_back(i, rook_pos_row);
        } else if ( current_board[{i, rook_pos_row}] >= enemy_first_letter &&
                    current_board[{i, rook_pos_row}] <= enemy_last_letter ) {
            moves.emplace_back(i, rook_pos_row);
            //gegnerische figur schlagen
            break;
        } else
            break;
    }


    return moves;


}


std::vector<Pos> Rook::possible_move(std::map<std::pair<int, int>, char> &current_board) const {
    std::vector<Pos> moves;
    if ( _piece_color == 'w' ) {
        moves = possible_moves_helper(current_board, CHESS::BLACKPIECE[0], CHESS::BLACKPIECE[1]);
    } else {
        moves = possible_moves_helper(current_board, CHESS::WHITEPIECE[0], CHESS::WHITEPIECE[1]);
    }
    return moves;
}
/////////////////////////////////////Rook-Ende//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////Bishop//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Bishop::Bishop(char name, char color, int col, int row) : Piece(name, color, col, row) {}


std::vector<Pos>
Bishop::possible_moves_helper(std::map<std::pair<int, int>, char> current_board, char enemy_first_letter,
                              char enemy_last_letter) const {
    std::vector<Pos> moves;
    int bishop_col = _pos.get_col();
    int bishop_row = _pos.get_row();

    // rechts oben
    for ( int i = 1; bishop_col + i <= CHESS::COLMAX && bishop_row + i <= CHESS::ROWMAX; i++ ) {
        char piece = current_board[{bishop_col + i, bishop_row + i}];
        if ( piece == CHESS::EMPTYSPACE ) {
            moves.emplace_back(bishop_col + i, bishop_row + i);
        } else if ( piece >= enemy_first_letter && piece <= enemy_last_letter ) {
            moves.emplace_back(bishop_col + i, bishop_row + i);
            break;
        } else {
            break;
        }
    }

    // links oben
    for ( int i = 1; bishop_col - i >= CHESS::COLMIN && bishop_row + i <= CHESS::ROWMAX; i++ ) {
        char piece = current_board[{bishop_col - i, bishop_row + i}];
        if ( piece == CHESS::EMPTYSPACE ) {
            moves.emplace_back(bishop_col - i, bishop_row + i);
        } else if ( piece >= enemy_first_letter && piece <= enemy_last_letter ) {
            moves.emplace_back(bishop_col - i, bishop_row + i);
            break;
        } else {
            break;
        }
    }

    // rechts unten
    for ( int i = 1; bishop_col + i <= CHESS::COLMAX && bishop_row - i >= CHESS::ROWMIN; i++ ) {
        char piece = current_board[{bishop_col + i, bishop_row - i}];
        if ( piece == CHESS::EMPTYSPACE ) {
            moves.emplace_back(bishop_col + i, bishop_row - i);
        } else if ( piece >= enemy_first_letter && piece <= enemy_last_letter ) {
            moves.emplace_back(bishop_col + i, bishop_row - i);
            break;
        } else {
            break;
        }
    }

    // links unten
    for ( int i = 1; bishop_col - i >= CHESS::COLMIN && bishop_row - i >= CHESS::ROWMIN; i++ ) {
        char piece = current_board[{bishop_col - i, bishop_row - i}];
        if ( piece == CHESS::EMPTYSPACE ) {
            moves.emplace_back(bishop_col - i, bishop_row - i);
        } else if ( piece >= enemy_first_letter && piece <= enemy_last_letter ) {
            moves.emplace_back(bishop_col - i, bishop_row - i);
            break;
        } else {
            break;
        }
    }

    return moves;
}


std::vector<Pos> Bishop::possible_move(std::map<std::pair<int, int>, char> &current_board) const {
    if ( _piece_color == 'w' ) {
        return possible_moves_helper(current_board, CHESS::BLACKPIECE[0], CHESS::BLACKPIECE[1]);
    } else {
        return possible_moves_helper(current_board, CHESS::WHITEPIECE[0], CHESS::WHITEPIECE[1]);
    }
}

/////////////////////////////////////Bishop-Ende//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////Knight//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Knight::Knight(char name, char color, int col, int row) : Piece(name, color, col, row) {}


std::vector<Pos>
Knight::possible_moves_helper(std::map<std::pair<int, int>, char> current_board, char enemy_first_letter,
                              char enemy_last_letter) const {
    std::vector<Pos> moves;

    // Alle 8 möglichen Bewegungen eines Springers
    std::vector<std::pair<int, int>> offsets = {
            {1,  2},
            {2,  1},
            {-1, 2},
            {-2, 1},
            {2,  -1},
            {1,  -2},
            {-2, -1},
            {-1, -2}
    };
    int col = _pos.get_col();
    int row = _pos.get_row();

    for ( auto [dc, dr]: offsets ) {
        int nc = col + dc;
        int nr = row + dr;
        //schauen ob einer der moves out of range sind
        if ( nc >= CHESS::COLMIN && nc <= CHESS::COLMAX && nr >= CHESS::ROWMIN && nr <= CHESS::ROWMAX ) {

            char target = current_board[{nc, nr}];

            //schauen ob eine mögliche springerbewegung ein freies oder gegnerische figur ist
            if ( target == CHESS::EMPTYSPACE || (target >= enemy_first_letter && target <= enemy_last_letter)) {
                moves.emplace_back(nc, nr);
            }
        }
    }

    return moves;
}


std::vector<Pos> Knight::possible_move(std::map<std::pair<int, int>, char> &current_board) const {
    if ( _piece_color == 'w' ) {
        return possible_moves_helper(current_board, CHESS::BLACKPIECE[0], CHESS::BLACKPIECE[1]);
    } else {
        return possible_moves_helper(current_board, CHESS::WHITEPIECE[0], CHESS::WHITEPIECE[1]);
    }
}

/////////////////////////////////////Knight-Ende//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////Queen//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Queen::Queen(char name, char color, int col, int row) : Piece(name, color, col, row) {}


std::vector<Pos>
Queen::possible_moves_helper(std::map<std::pair<int, int>, char> current_board, char enemy_first_letter,
                             char enemy_last_letter) const {
    std::vector<Pos> moves;
    int col = _pos.get_col();
    int row = _pos.get_row();

    // Vertikale und horizontale Richtungen (4)
    for ( int i = row + 1; i <= CHESS::ROWMAX; i++ ) {
        if ( current_board[{col, i}] == CHESS::EMPTYSPACE ) {
            moves.emplace_back(col, i);
        } else if ( current_board[{col, i}] >= enemy_first_letter && current_board[{col, i}] <= enemy_last_letter ) {
            moves.emplace_back(col, i);
            break;
        } else break;
    }

    for ( int i = row - 1; i >= CHESS::ROWMIN; i-- ) {
        if ( current_board[{col, i}] == CHESS::EMPTYSPACE ) {
            moves.emplace_back(col, i);
        } else if ( current_board[{col, i}] >= enemy_first_letter && current_board[{col, i}] <= enemy_last_letter ) {
            moves.emplace_back(col, i);
            break;
        } else break;
    }

    for ( int i = col + 1; i <= CHESS::COLMAX; i++ ) {
        if ( current_board[{i, row}] == CHESS::EMPTYSPACE ) {
            moves.emplace_back(i, row);
        } else if ( current_board[{i, row}] >= enemy_first_letter && current_board[{i, row}] <= enemy_last_letter ) {
            moves.emplace_back(i, row);
            break;
        } else break;
    }

    for ( int i = col - 1; i >= CHESS::COLMIN; i-- ) {
        if ( current_board[{i, row}] == CHESS::EMPTYSPACE ) {
            moves.emplace_back(i, row);
        } else if ( current_board[{i, row}] >= enemy_first_letter && current_board[{i, row}] <= enemy_last_letter ) {
            moves.emplace_back(i, row);
            break;
        } else break;
    }

    // Diagonalrichtungen (4)
    for ( int i = 1; col + i <= CHESS::COLMAX && row + i <= CHESS::ROWMAX; i++ ) {
        if ( current_board[{col + i, row + i}] == CHESS::EMPTYSPACE ) {
            moves.emplace_back(col + i, row + i);
        } else if ( current_board[{col + i, row + i}] >= enemy_first_letter &&
                    current_board[{col + i, row + i}] <= enemy_last_letter ) {
            moves.emplace_back(col + i, row + i);
            break;
        } else break;
    }

    for ( int i = 1; col - i >= CHESS::COLMIN && row + i <= CHESS::ROWMAX; i++ ) {
        if ( current_board[{col - i, row + i}] == CHESS::EMPTYSPACE ) {
            moves.emplace_back(col - i, row + i);
        } else if ( current_board[{col - i, row + i}] >= enemy_first_letter &&
                    current_board[{col - i, row + i}] <= enemy_last_letter ) {
            moves.emplace_back(col - i, row + i);
            break;
        } else break;
    }

    for ( int i = 1; col + i <= CHESS::COLMAX && row - i >= CHESS::ROWMIN; i++ ) {
        if ( current_board[{col + i, row - i}] == CHESS::EMPTYSPACE ) {
            moves.emplace_back(col + i, row - i);
        } else if ( current_board[{col + i, row - i}] >= enemy_first_letter &&
                    current_board[{col + i, row - i}] <= enemy_last_letter ) {
            moves.emplace_back(col + i, row - i);
            break;
        } else break;
    }

    for ( int i = 1; col - i >= CHESS::COLMIN && row - i >= CHESS::ROWMIN; i++ ) {
        if ( current_board[{col - i, row - i}] == CHESS::EMPTYSPACE ) {
            moves.emplace_back(col - i, row - i);
        } else if ( current_board[{col - i, row - i}] >= enemy_first_letter &&
                    current_board[{col - i, row - i}] <= enemy_last_letter ) {
            moves.emplace_back(col - i, row - i);
            break;
        } else break;
    }

    return moves;
}


std::vector<Pos> Queen::possible_move(std::map<std::pair<int, int>, char> &current_board) const {
    if ( _piece_color == 'w' ) {
        return possible_moves_helper(current_board, CHESS::BLACKPIECE[0], CHESS::BLACKPIECE[1]);
    } else {
        return possible_moves_helper(current_board, CHESS::WHITEPIECE[0], CHESS::WHITEPIECE[1]);
    }
}


/////////////////////////////////////Queen-Ende//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////King///////////////////////////////////////////////////////////////////////////////////////
King::King(char name, char color, int col, int row) : Piece(name, color, col, row) {}


std::vector<Pos> King::possible_moves_helper(std::map<std::pair<int, int>, char> current_board, char enemy_first_letter,
                                             char enemy_last_letter) const {
    std::vector<Pos> moves;
    int col = _pos.get_col();
    int row = _pos.get_row();

    // Alle 8 möglichen Richtungen
    std::vector<std::pair<int, int>> directions = {
            {0,  1},   // oben
            {1,  1},  // rechts oben
            {1,  0},   // rechts
            {1,  -1},  // rechts unten
            {0,  -1},   // unten
            {-1, 0},   // links
            {-1, -1},  // links unten
            {-1, 1}   // links oben
    };

    for ( auto [dc, dr]: directions ) {
        int nc = col + dc;
        int nr = row + dr;

        if ( nc >= CHESS::COLMIN && nc <= CHESS::COLMAX &&
             nr >= CHESS::ROWMIN && nr <= CHESS::ROWMAX ) {

            char target = current_board[{nc, nr}];

            if ( target == CHESS::EMPTYSPACE || (target >= enemy_first_letter && target <= enemy_last_letter)) {
                moves.emplace_back(nc, nr);
            }
        }
    }

    return moves;
}


std::vector<Pos> King::possible_move(std::map<std::pair<int, int>, char> &current_board) const {
    if ( _piece_color == 'w' ) {
        return possible_moves_helper(current_board, CHESS::BLACKPIECE[0], CHESS::BLACKPIECE[1]);
    } else {
        return possible_moves_helper(current_board, CHESS::WHITEPIECE[0], CHESS::WHITEPIECE[1]);
    }
}

/////////////////////////////////////King-Ende///////////////////////////////////////////////////////////////////////////////////////


