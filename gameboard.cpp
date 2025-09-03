
// Created by Jenush on 06.06.2025.
//

#include "gameboard.h"
#include <iostream>
#include <cassert>

class Pawn;


GameBoard::GameBoard() {
    setup_start_position();
}


std::vector<Pos> GameBoard::check_pawn_promotion() {
    std::vector<Pos> promotion_moves;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////schauen ob weißer oder schwarzer bauer in der Promotion Row ist weil dann muss man ein speziellen move hinzufügen/////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    for ( int i = CHESS::COLMIN; i <= CHESS::COLMAX; i++ ) {
        if ( _current_board[{i, CHESS::ROWMAX}] == 'P' ) {
            _promotion = true; //auf true setzen damit man im gamewidget weiß das die zusätzlichen felder gemalt werden müssen
            //extra felder die bei promotion angezeigt werden
            _current_board[{9, CHESS::ROWMAX}] = 'Q';
            _current_board[{10, CHESS::ROWMAX}] = 'R';
            _current_board[{11, CHESS::ROWMAX}] = 'B';
            _current_board[{12, CHESS::ROWMAX}] = 'N';
            promotion_moves.emplace_back(9, CHESS::ROWMAX);
            promotion_moves.emplace_back(10, CHESS::ROWMAX);
            promotion_moves.emplace_back(11, CHESS::ROWMAX);
            promotion_moves.emplace_back(12, CHESS::ROWMAX);
        }
        if ( _current_board[{i, CHESS::ROWMIN}] == 'p' ) {
            _promotion = true;
            _current_board[{9, CHESS::ROWMAX}] = 'q';
            _current_board[{10, CHESS::ROWMAX}] = 'r';
            _current_board[{11, CHESS::ROWMAX}] = 'b';
            _current_board[{12, CHESS::ROWMAX}] = 'n';
            promotion_moves.emplace_back(9, CHESS::ROWMAX);
            promotion_moves.emplace_back(10, CHESS::ROWMAX);
            promotion_moves.emplace_back(11, CHESS::ROWMAX);
            promotion_moves.emplace_back(12, CHESS::ROWMAX);
        }
    }
    return promotion_moves;
}


void GameBoard::check_castling(std::vector<Pos> &castling_moves) {
    char turn = check_turn();
    int row = (turn == 'w') ? CHESS::ROWMIN : CHESS::ROWMAX;
    char king = (turn == 'w') ? 'K' : 'k';
    char rook = (turn == 'w') ? 'R' : 'r';

    // Ausgangspositionen
    Pos kingPos(5, row);       // e1 oder e8
    Pos shortRookPos(8, row);  // h1 oder h8
    Pos longRookPos(1, row);   // a1 oder a8

    // Flags, ob König oder Türme bewegt wurden
    bool kingMoved = false;
    bool shortRookMoved = false;
    bool longRookMoved = false;

    for ( const auto &board: _board_history ) {
        // König bewegt
        auto kingIt = board.find({kingPos.get_col(), kingPos.get_row()});
        if ( kingIt->second != king ) {
            kingMoved = true;
            break;
        }

        // Rook kurz bewegt

        auto rookShortIt = board.find({shortRookPos.get_col(), shortRookPos.get_row()});
        if ( rookShortIt->second != rook ) {
            shortRookMoved = true;
        }

        // Rook lang bewegt
        auto rookLongIt = board.find({longRookPos.get_col(), longRookPos.get_row()});
        if ( rookLongIt->second != rook ) {
            longRookMoved = true;
        }

    }

    // Short Castling prüfen
    if ( !kingMoved && !shortRookMoved ) {
        //prüfen das zwischen rook und könig keine figuren sind
        bool free1 = _current_board[{6, row}] == CHESS::EMPTYSPACE;
        bool free2 = _current_board[{7, row}] == CHESS::EMPTYSPACE;
        if ( free1 && free2 && !is_check(turn)) {
            castling_moves.emplace_back(7, row); // g1 oder g8
            //kommt es hier rein
        }
    }

    // Long Castling prüfen
    if ( !kingMoved && !longRookMoved ) {
        //prüfen das zwischen rook und könig keine figuren sind
        bool free1 = _current_board[{2, row}] == '-';
        bool free2 = _current_board[{3, row}] == '-';
        bool free3 = _current_board[{4, row}] == '-'; // d1 oder d8
        if ( free1 && free2 && free3 && !is_check(turn)) {
            castling_moves.emplace_back(3, row); // c1 oder c8
        }
    }
}


void GameBoard::check_en_passant(std::vector<Pos> &en_passant_moves, int pawn_col, int pawn_row) {
    char turn = check_turn();

    if ( turn == 'w' ) {
        // En Passant ist nur möglich, wenn ein weißer Bauer auf Reihe 5 steht
        if ( pawn_row == CHESS::ENPASSANTROWWHTE && _turn > 0 ) {
            auto &last_board = _board_history[_turn - 2];//weil turn mit 0 startet
            auto &current_board = _board_history[_turn - 1];

            // Prüfe linken und rechten Nachbarn vom Pawn
            for ( int offset: {-1, 1} ) {
                int neighbor_col = pawn_col + offset;
                if ( neighbor_col < CHESS::COLMIN || neighbor_col > CHESS::COLMAX ) continue;

                std::pair<int, int> from = {neighbor_col, 7};  // vorherige Position des schwarzen Bauern
                std::pair<int, int> to = {neighbor_col, 5};    // aktuelle Position

                // Wurde der Bauer gerade zwei Felder vorgerückt
                /*Dazu muss geschaut werden ob beim letzten board ein Bauer in der Ausgangsposition stand
                 * und ob beim jetzigen board der Bauer zwei felder vorgerückt ist
                 */
                if ( last_board[{from}] == 'p' && current_board[{to}] == 'p' &&
                     current_board[{from}] == CHESS::EMPTYSPACE ) {
                    // En passant zug ist möglich
                    en_passant_moves.emplace_back(neighbor_col, CHESS::ENPASSANTCAPTUREROWWHTE);
                }
            }
        }

    } else {
        // En Passant ist nur möglich, wenn ein schwarzer Bauer auf Reihe 4 steht
        if ( pawn_row == CHESS::ENPASSANTROWBLACK && _turn > 0 ) {
            auto &last_board = _board_history[_turn - 2];//weil turn mit 0 startet
            auto &current_board = _board_history[_turn - 1];

            // Prüfe linken und rechten Nachbarn
            for ( int dc: {-1, 1} ) {
                int neighbor_col = pawn_col + dc;
                if ( neighbor_col < CHESS::COLMIN || neighbor_col > CHESS::COLMAX ) continue;

                std::pair<int, int> from = {neighbor_col, 2};  // vorherige Position des weißen Bauern
                std::pair<int, int> to = {neighbor_col, 4};    // aktuelle Position

                // Wurde der Bauer gerade zwei Felder vorgerückt

                if ( last_board[{from}] == 'P' && current_board[{to}] == 'P' && current_board[{from}] == '-' ) {
                    // En Passant-Zug ist möglich
                    en_passant_moves.emplace_back(neighbor_col, CHESS::ENPASSANTCAPTURERBLACK);
                }
            }
        }
    }
}


std::vector<Pos> GameBoard::get_possible_moves(int row, int col) {
    std::vector<Pos> move;


    ///////////////////////////////////////////////////////////////////////////////
    /////////////////spezielle moves wie promotion,castling,en passent/////////////
    /////////////////wurde in gameboard gelöst weil man auch zugriff///////////////
    ////////////////auf andere pieces braucht//////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    //promotion
    std::vector<Pos> legalmove = check_pawn_promotion();


    if ( !legalmove.empty()) {
        //heißt also es muss eine promotion gemacht werden
        return legalmove;

    }

    auto board_before_change = _current_board;
    for ( Piece *piece: _pieces ) {
        if ( check_turn() == piece->_piece_color ) {
            if ( piece->_pos.get_col() == col && piece->_pos.get_row() == row ) {


                move = piece->possible_move(_current_board);
                if ( piece->_piece_name == 'K' || piece->_piece_name == 'k' ) {
                    //castling moves gegebenenfalls hinzufügen
                    check_castling(legalmove);
                } else if ( piece->_piece_name == 'P' || piece->_piece_name == 'p' ) {
                    check_en_passant(legalmove, piece->_pos.get_col(), piece->_pos.get_row());
                }

                for ( Pos pos: move ) {
                    //erstmal wird der move gemacht

                    //gelöschtes piece muss gegebenenfalls gespeichert werden weil es ja vielleicht kein legaler zug war
                    //damit man es wieder in pieces aufnehmen kann
                    Piece *deletedPiece = capture_piece(pos.get_col(), pos.get_row());
                    Pos posbefore(piece->_pos.get_col(), piece->_pos.get_row());
                    piece->_pos.set(pos.get_col(), pos.get_row());
                    _current_board[{posbefore.get_col(), posbefore.get_row()}] = CHESS::EMPTYSPACE;
                    _current_board[{pos.get_col(), pos.get_row()}] = piece->_piece_name;

                    if ( is_check(piece->_piece_color) == true ) {

                        //schauen ob einer der moves zum check führt und gegebenenfalls nicht in legal moves aufnehmen
                        //weil das heißt das es gefesselt war und damit nicht legal ist

                        // Rückgängig machen
                        _current_board = board_before_change;
                        if ( deletedPiece ) _pieces.push_back(deletedPiece);
                        piece->_pos.set(posbefore.get_col(), posbefore.get_row());
                        //aus move diesen pos rauswerfen

                    } else {

                        //war kein schach
                        legalmove.push_back(pos);
                        // Rückgängig machen
                        _current_board = board_before_change;
                        if ( deletedPiece ) _pieces.push_back(deletedPiece);
                        piece->_pos.set(posbefore.get_col(), posbefore.get_row());

                    }
                }


            }

        }


    }
    return legalmove;
}


Piece *GameBoard::capture_piece(int col, int row) {
    for ( auto it = _pieces.begin(); it != _pieces.end(); ) {
        if ((*it)->_pos.get_col() == col && (*it)->_pos.get_row() == row ) {
            Piece *deleted_piece = *it;
            _pieces.erase(it);
            assert(deleted_piece != nullptr &&
                   "capture_piece gibt nullptr zurück sollte aber eigentlich nicht passieren.");


            return deleted_piece;
        } else {
            ++it;
        }
    }
    return nullptr;
}


//setzen von move und update von board
void GameBoard::set_cell(int colbefore, int rowbefore, int col, int row) {

    for ( Piece *piece: _pieces ) {
        if ( piece->_pos.get_col() == colbefore && piece->_pos.get_row() == rowbefore ) {
            //sonderfall für promotion
            if ( _promotion ) {
                //
                _current_board[{colbefore, rowbefore}] = _current_board[{col, row}];
                Piece *deletepawn = capture_piece(colbefore, rowbefore);
                //führt zu kein fehler weil nullptr delten kann
                delete deletepawn;

                //man kann nicht durch pieces iterien weil gegebenenfalls die Figur nicht mehr auf dem board steht deshalb manuell und weil man das in pieces pushen muss
                if ( _current_board[{col, row}] == 'Q' ) {
                    _pieces.push_back(new Queen('Q', 'w', colbefore, rowbefore));

                }
                if ( _current_board[{col, row}] == 'q' ) {
                    _pieces.push_back(new Queen(_current_board[{col, row}], 'b', colbefore, rowbefore));

                }
                if ( _current_board[{col, row}] == 'R' ) {
                    _pieces.push_back(new Rook(_current_board[{col, row}], 'w', colbefore, rowbefore));

                }
                if ( _current_board[{col, row}] == 'r' ) {
                    _pieces.push_back(new Rook(_current_board[{col, row}], 'b', colbefore, rowbefore));

                }
                if ( _current_board[{col, row}] == 'B' ) {
                    _pieces.push_back(new Bishop(_current_board[{col, row}], 'w', colbefore, rowbefore));

                }
                if ( _current_board[{col, row}] == 'b' ) {
                    _pieces.push_back(new Bishop(_current_board[{col, row}], 'b', colbefore, rowbefore));

                }
                if ( _current_board[{col, row}] == 'N' ) {
                    _pieces.push_back(new Knight(_current_board[{col, row}], 'w', colbefore, rowbefore));

                }
                if ( _current_board[{col, row}] == 'n' ) {
                    _pieces.push_back(new Knight(_current_board[{col, row}], 'b', colbefore, rowbefore));

                }


            } else {
                //normaler ablauf
                //wenn ein piece dort gestanden hat wird es gelöscht
                Piece *deletedPiece = capture_piece(col, row);
                delete deletedPiece;
                //aktuelle figur setzen
                piece->_pos.set(col, row);

                _current_board[{colbefore, rowbefore}] = CHESS::EMPTYSPACE;
                _current_board[{col, row}] = piece->_piece_name;
                std::vector<Pos> en_passent_moves;
                check_en_passant(en_passent_moves, colbefore,
                                 rowbefore); //nur um zu gucken ob es ein en passent move war


                //schauen ob es ein castling move war
                if ( piece->_piece_name == 'K' ) {
                    //short castlen
                    if ( colbefore == 5 && rowbefore == 1 ) {
                        //short castlen
                        if ( col == 7 && row == 1 ) {
                            _current_board[{8, 1}] = CHESS::EMPTYSPACE;
                            _current_board[{6, 1}] = 'R';
                            for ( Piece *p: _pieces ) {
                                if ( p->_piece_name == 'R' && p->_pos.get_col() == 8 && p->_pos.get_row() == 1 ) {
                                    p->_pos.set(6, 1);
                                    break;
                                }
                            }

                        }
                            //long castlen
                        else if ( col == 3 && row == 1 ) {
                            _current_board[{1, 1}] = CHESS::EMPTYSPACE;
                            _current_board[{4, 1}] = 'R';

                            for ( Piece *p: _pieces ) {
                                if ( p->_piece_name == 'R' && p->_pos.get_col() == 1 && p->_pos.get_row() == 1 ) {
                                    p->_pos.set(4, 1);
                                    break;
                                }
                            }
                        }
                    }
                } else if ( piece->_piece_name == 'k' ) {
                    //short castlen
                    if ( colbefore == 5 && rowbefore == 8 ) {
                        //short castlen
                        if ( col == 7 && row == 8 ) {
                            _current_board[{8, 8}] = CHESS::EMPTYSPACE;
                            _current_board[{6, 8}] = 'R';
                            for ( Piece *p: _pieces ) {
                                if ( p->_piece_name == 'R' && p->_pos.get_col() == 8 && p->_pos.get_row() == 8 ) {
                                    p->_pos.set(6, 8);
                                    break;
                                }
                            }

                        }
                            //long castlen
                        else if ( col == 3 && row == 8 ) {
                            _current_board[{1, 8}] = CHESS::EMPTYSPACE;
                            _current_board[{4, 8}] = 'R';

                            for ( Piece *p: _pieces ) {
                                if ( p->_piece_name == 'R' && p->_pos.get_col() == 1 && p->_pos.get_row() == 8 ) {
                                    p->_pos.set(4, 8);
                                    break;
                                }
                            }
                        }
                    }
                } else if ( !en_passent_moves.empty()) {
                    if ( en_passent_moves[0].get_row() == row && en_passent_moves[0].get_col() == col ) {
                        //die figur die geschlagen wird befindet sich eine reihe unter der jetzigen pawn figur bei weiß
                        if ( piece->_piece_color == 'w' ) {
                            capture_piece(col, row - 1);
                            _current_board[{col, row - 1}] = CHESS::EMPTYSPACE;
                        } else {
                            //bei schawarz dann genau anders herum
                            capture_piece(col, row + 1);
                            _current_board[{col, row + 1}] = CHESS::EMPTYSPACE;

                        }
                    }
                }

                //darf bei pawn promotion nicht erhöht werden und feld muss dann auch nicht gespeichert werden
                _turn++;
                _board_history.push_back(_current_board);


            }


        }
    }


    check_game_state();

}


void GameBoard::print_gameboard() {

    for ( int i = 8; i >= 1; i-- ) {
        for ( int j = 1; j < 9; j++ ) {
            std::cout << _current_board[{j, i}];
        }
        std::cout << std::endl;
    }
}


char GameBoard::check_turn() const {
    if ( _turn % 2 == 1 ) {

        return 'b';
    } else {

        return 'w';
    }
}


bool GameBoard::is_check(char color) {
    Pos kingPos;

    // König finden
    for ( Piece *piece: _pieces ) {
        if ((piece->_piece_name == 'K' && piece->_piece_color == color) ||
            (piece->_piece_name == 'k' && piece->_piece_color == color)) {

            kingPos = piece->_pos;
            break;
        }
    }



    // Prüfen, ob König bedroht
    for ( Piece *piece: _pieces ) {
        if ( piece->_piece_color != color ) {
            auto moves = piece->possible_move(_current_board);
            for ( auto move: moves ) {
                if ( move.get_col() == kingPos.get_col() && move.get_row() == kingPos.get_row()) {
                    return true;
                }
            }
        }
    }
    return false;
}


std::string GameBoard::draw_50_moves() {
    int count_no_progress = 0;
    int piece_before = 0;
    int piece_after = 0;
    bool pawn_moved = false;

    // Letzen 50 züge prüfen von hinten da man dann vorzeitig abrechen kann wenn in 50 zügen kein fortschritt gemacht wurde
    //kein Fortschritt heißt kein Bauer wurde bewegt oder es wurde keine Figur geschlagen
    for ( int i = _board_history.size() - 1; i > 0 && count_no_progress < 50; --i ) {

        // Prüfe alle Felder
        for ( int row = CHESS::ROWMIN; row <= CHESS::ROWMAX; ++row ) {
            for ( int col = CHESS::COLMIN; col <= CHESS::COLMAX; ++col ) {
                std::pair<int, int> pos = {col, row};
                char before = _board_history[i - 1].at(pos);
                char after = _board_history[i].at(pos);

                // Bauer wurde bewegt
                if ((before == 'p' || before == 'P') && after == CHESS::EMPTYSPACE ) {
                    pawn_moved = true;
                }


                // Figuranzahl zählen
                if ( before != CHESS::EMPTYSPACE ) piece_before++;
                if ( after != CHESS::EMPTYSPACE ) piece_after++;
            }
        }

        //wenn bauer bewegt wurde oder die anzahl der pieces nicht übereinstimmt verlässt man die schleife
        if ( pawn_moved || piece_before != piece_after ) {
            break;
        }

        count_no_progress++;
    }

    if ( count_no_progress >= 50 ) {
        return "unentschieden";
    } else {
        return "kein unentschieden";
    }
}


std::string GameBoard::draw_few_material() {
    /*Wenn Bauern existieren ist nicht wegen unzureichenden Material das Spiel beendet
     * Wenn der König und nur ein Läufer oder nur ein Pferd auf dem Feld sind
     * ->dann ist es ein unentschieden pro seite
     */
    int count_material = 0;
    int count_knight_bishop_white = 0;
    int count_knight_bishop_black = 0;


    for ( int i = 8; i >= 1; i-- ) {
        for ( int j = 1; j < 9; j++ ) {
            //diese Bedingung prüft ob es eine Figur gibt ausser dem könig
            if ( _current_board[{j, i}] != CHESS::EMPTYSPACE && _current_board[{j, i}] != 'k' &&
                 _current_board[{j, i}] != 'K' ) {
                count_material++;
            }
            if ( _current_board[{j, i}] == 'B' || _current_board[{j, i}] == 'N' ) {
                count_knight_bishop_white++;
            }
            if ( _current_board[{j, i}] == 'b' || _current_board[{j, i}] == 'n' ) {
                count_knight_bishop_black++;
            }
        }
        if ( count_material > 2 ) {
            return "kein unentschieden";

        }
        //heißt also maximal ein Läufer oder Pferd pro Seite
        if ( count_knight_bishop_white <= 1 && count_knight_bishop_black <= 1 ) {
            return "unentschieden";

        }


    }
    return "kein unentschieden";

}


std::string GameBoard::draw_repetition() {
    int repetition_count = 0;

    for ( const auto &past_board: _board_history ) {
        if ( past_board == _current_board ) {
            repetition_count++;
        }
    }

    if ( repetition_count >= 3 ) {
        _message = "unentschieden";
        return "unentschieden";
    }


    return "kein unentschieden";


}


std::string GameBoard::check_stalemate_win() {
    bool hasLegalMove = false;
    auto board_before_change = _current_board;


    for ( Piece *piece: _pieces ) {
        if ( check_turn() != piece->_piece_color ) continue;

        auto moves = piece->possible_move(_current_board);
        for ( Pos &pos: moves ) {
            Pos old_pos = piece->_pos;
            Piece *captured = capture_piece(pos.get_col(), pos.get_row());

            piece->_pos = pos;
            _current_board[{old_pos.get_col(), old_pos.get_row()}] = CHESS::EMPTYSPACE;
            _current_board[{pos.get_col(), pos.get_row()}] = piece->_piece_name;

            if ( !is_check(check_turn())) {
                // Es gibt einen legalen Zug
                hasLegalMove = true;
            }

            // Rückgängig machen
            piece->_pos = old_pos;
            _current_board = board_before_change;
            if ( captured != nullptr )
                _pieces.push_back(captured);

        }

        if ( hasLegalMove ) break;
    }

    if ( !hasLegalMove ) {
        if ( is_check(check_turn())) {
            return "gewonnen";
        } else {
            return "unentschieden";
        }
    }
    return "kein ergebnis";
}


std::string GameBoard::check_game_state() {

    std::string draw = "unentschieden";
    if ( draw_repetition() == draw ) {
        _message = "unentschieden";
    }
    if ( draw_50_moves() == draw ) {
        _message = "unentschieden";
    }
    if ( draw_few_material() == draw ) {
        _message = "unentschieden";
    }
    if ( check_stalemate_win() == "gewonnen" ) {
        _message = "gewonnen";
    }

    return "kein ergebnis";
}


void GameBoard::reset() {
    for ( Piece *p: _pieces )
        delete p;
    _pieces.clear();
    _current_board.clear();
    _board_history.clear();
    _turn = 0;
    _promotion = false;
    _message = "";

    // Dann initialisiere wieder alles:
    setup_start_position();  // oder nochmal eigene Init-Methode aufrufen
}


void ::GameBoard::setup_start_position() {
    //Aufbau des Feldes mit gesetzten Figuren
    //weiß
    _pieces.push_back(new Pawn('P', 'w', 1, 2));
    _pieces.push_back(new Pawn('P', 'w', 2, 2));
    _pieces.push_back(new Pawn('P', 'w', 3, 2));
    _pieces.push_back(new Pawn('P', 'w', 4, 2));
    _pieces.push_back(new Pawn('P', 'w', 5, 2));
    _pieces.push_back(new Pawn('P', 'w', 6, 2));
    _pieces.push_back(new Pawn('P', 'w', 7, 2));
    _pieces.push_back(new Pawn('P', 'w', 8, 2));
    _pieces.push_back(new Rook('R', 'w', 1, 1));
    _pieces.push_back(new Rook('R', 'w', 8, 1));
    _pieces.push_back(new Knight('N', 'w', 7, 1));
    _pieces.push_back(new Knight('N', 'w', 2, 1));
    _pieces.push_back(new Bishop('B', 'w', 6, 1));
    _pieces.push_back(new Bishop('B', 'w', 3, 1));
    _pieces.push_back(new King('K', 'w', 5, 1));
    _pieces.push_back(new Queen('Q', 'w', 4, 1));

    _pieces.push_back(new Pawn('p', 'b', 1, 7));
    _pieces.push_back(new Pawn('p', 'b', 2, 7));
    _pieces.push_back(new Pawn('p', 'b', 3, 7));
    _pieces.push_back(new Pawn('p', 'b', 4, 7));
    _pieces.push_back(new Pawn('p', 'b', 5, 7));
    _pieces.push_back(new Pawn('p', 'b', 6, 7));
    _pieces.push_back(new Pawn('p', 'b', 7, 7));
    _pieces.push_back(new Pawn('p', 'b', 8, 7));
    _pieces.push_back(new Rook('r', 'b', 1, 8));
    _pieces.push_back(new Rook('r', 'b', 8, 8));
    _pieces.push_back(new Knight('n', 'b', 7, 8));
    _pieces.push_back(new Knight('n', 'b', 2, 8));
    _pieces.push_back(new Bishop('b', 'b', 6, 8));
    _pieces.push_back(new Bishop('b', 'b', 3, 8));
    _pieces.push_back(new King('k', 'b', 5, 8));
    _pieces.push_back(new Queen('q', 'b', 4, 8));


    for ( int i = CHESS::COLMIN; i <= CHESS::COLMAX; i++ ) {
        //setzen der pawns
        _current_board[{i, 2}] = 'P';
        _current_board[{i, 7}] = 'p';

    }

    //für weiß
    _current_board[{1, 1}] = 'R';
    _current_board[{8, 1}] = 'R';
    _current_board[{7, 1}] = 'N';
    _current_board[{2, 1}] = 'N';
    _current_board[{3, 1}] = 'B';
    _current_board[{6, 1}] = 'B';
    _current_board[{5, 1}] = 'K';
    _current_board[{4, 1}] = 'Q';

    //für schwarz
    _current_board[{1, 8}] = 'r';
    _current_board[{8, 8}] = 'r';
    _current_board[{7, 8}] = 'n';
    _current_board[{2, 8}] = 'n';
    _current_board[{3, 8}] = 'b';
    _current_board[{6, 8}] = 'b';
    _current_board[{5, 8}] = 'k';
    _current_board[{4, 8}] = 'q';

    //rest leere felder
    for ( int i = 3; i < 7; i++ ) {
        for ( int j = 0; j < 9; j++ ) {
            _current_board[{j, i}] = CHESS::EMPTYSPACE;
        }
    }
}


GameBoard::~GameBoard() {
    for ( Piece *piece: _pieces ) {
        delete piece;
    }
    _pieces.clear();
}

