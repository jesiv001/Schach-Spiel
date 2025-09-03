//
// Created by Jenush on 06.06.2025.
//


#include "gamewidget.h"
#include "gameenddialog.h"
#include <QPainter>
#include <QPixmap>
#include <QDir>
#include <iostream>
#include <QMouseEvent>
#include <QMessageBox>
#include <QApplication>

using namespace Qt;


GameWidget::GameWidget(QWidget *parent)
        : QWidget(parent) {
    setFixedSize(1200, 800); // 75x50 Zellen


    // kleinbuchstaben = schwarze figuren
    // großbuchstaben = weiße figuren
    _piece_image['p'] = "piece_picture/pawn_black.png";
    _piece_image['P'] = "piece_picture/pawn_white.png";
    _piece_image['Q'] = "piece_picture/queen_white.png";
    _piece_image['q'] = "piece_picture/queen_black.png";
    _piece_image['K'] = "piece_picture/king_white.png";
    _piece_image['k'] = "piece_picture/king_black.png";
    _piece_image['K'] = "piece_picture/king_white.png";
    _piece_image['N'] = "piece_picture/knight_white.png";
    _piece_image['n'] = "piece_picture/knight_black.png";
    _piece_image['b'] = "piece_picture/bishop_black.png";
    _piece_image['B'] = "piece_picture/bishop_white.png";
    _piece_image['r'] = "piece_picture/rook_black.png";
    _piece_image['R'] = "piece_picture/rook_white.png";
}


void GameWidget::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    drawBoard(&painter);
    drawHighlights(&painter);

}


void GameWidget::drawBoard(QPainter *painter) {
    int counter = 0;
    int cellSize = (width() - 400) /
                   GameBoard::SIZE; //-400 weil das board nur 50x50 sein soll, der rest für die promotion-feld anzeige
    std::cout << width();
    QColor brown("#9C6B30");
    //malen des boards
    for ( int row = 7; row >= 0; row-- ) {
        counter++;

        for ( int col = 0; col < GameBoard::SIZE; ++col ) {
            QRect rect(col * cellSize, row * cellSize, cellSize, cellSize);
            painter->drawRect(rect);
            if ( counter % 2 == 0 ) {
                painter->fillRect(rect, brown);
            } else {
                painter->fillRect(rect, white);
            }


            counter++;
            int chessRow = GameBoard::SIZE - row;
            int chessCol = col + 1;
            auto piece = _board._current_board.find({chessCol, chessRow});


            if ( piece != _board._current_board.end()) {
                if ( piece->second == 'P' ) {

                    QPixmap pixmap(_piece_image['P']);
                    if ( !pixmap.isNull()) {
                        painter->drawPixmap(rect.topLeft(), pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio,
                                                                          Qt::SmoothTransformation));

                    } else {
                        qDebug() << "Versuche zu laden:" << _piece_image['P'];
                        qDebug() << "Existiert:" << _piece_image['P'];
                        qDebug() << "Geladen:" << !pixmap.isNull();
                        qDebug() << "Geladen:" << !pixmap.isNull();


                    }
                } else if ( piece->second == 'p' ) {

                    QPixmap pixmap(_piece_image['p']);
                    if ( !pixmap.isNull()) {
                        painter->drawPixmap(rect.topLeft(), pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio,
                                                                          Qt::SmoothTransformation));

                    } else {
                        qDebug() << "Versuche zu laden:" << _piece_image['p'];
                        qDebug() << "Existiert:" << _piece_image['p'];
                        qDebug() << "Geladen:" << !pixmap.isNull();
                        qDebug() << "Geladen:" << !pixmap.isNull();


                    }

                } else if ( piece->second == 'r' ) {


                    QPixmap pixmap(_piece_image['r']);
                    if ( !pixmap.isNull()) {
                        painter->drawPixmap(rect.topLeft(), pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio,
                                                                          Qt::SmoothTransformation));

                    } else {
                        qDebug() << "Versuche zu laden:" << _piece_image['r'];
                        qDebug() << "Existiert:" << _piece_image['r'];
                        qDebug() << "Geladen:" << !pixmap.isNull();
                        qDebug() << "Geladen:" << !pixmap.isNull();


                    }

                } else if ( piece->second == 'R' ) {

                    QPixmap pixmap(_piece_image['R']);
                    if ( !pixmap.isNull()) {
                        painter->drawPixmap(rect.topLeft(), pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio,
                                                                          Qt::SmoothTransformation));

                    } else {
                        qDebug() << "Versuche zu laden:" << _piece_image['R'];
                        qDebug() << "Existiert:" << _piece_image['R'];
                        qDebug() << "Geladen:" << !pixmap.isNull();
                        qDebug() << "Geladen:" << !pixmap.isNull();


                    }

                } else if ( piece->second == 'n' ) {

                    QPixmap pixmap(_piece_image['n']);
                    if ( !pixmap.isNull()) {
                        painter->drawPixmap(rect.topLeft(), pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio,
                                                                          Qt::SmoothTransformation));

                    } else {
                        qDebug() << "Versuche zu laden:" << _piece_image['n'];
                        qDebug() << "Existiert:" << _piece_image['n'];
                        qDebug() << "Geladen:" << !pixmap.isNull();
                        qDebug() << "Geladen:" << !pixmap.isNull();


                    }

                } else if ( piece->second == 'N' ) {

                    QPixmap pixmap(_piece_image['N']);
                    if ( !pixmap.isNull()) {
                        painter->drawPixmap(rect.topLeft(), pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio,
                                                                          Qt::SmoothTransformation));

                    } else {
                        qDebug() << "Versuche zu laden:" << _piece_image['N'];
                        qDebug() << "Existiert:" << _piece_image['N'];
                        qDebug() << "Geladen:" << !pixmap.isNull();
                        qDebug() << "Geladen:" << !pixmap.isNull();


                    }

                } else if ( piece->second == 'b' ) {

                    QPixmap pixmap(_piece_image['b']);
                    if ( !pixmap.isNull()) {
                        painter->drawPixmap(rect.topLeft(), pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio,
                                                                          Qt::SmoothTransformation));

                    } else {
                        qDebug() << "Versuche zu laden:" << _piece_image['b'];
                        qDebug() << "Existiert:" << _piece_image['b'];
                        qDebug() << "Geladen:" << !pixmap.isNull();
                        qDebug() << "Geladen:" << !pixmap.isNull();


                    }

                } else if ( piece->second == 'B' ) {

                    QPixmap pixmap(_piece_image['B']);
                    if ( !pixmap.isNull()) {
                        painter->drawPixmap(rect.topLeft(), pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio,
                                                                          Qt::SmoothTransformation));

                    } else {
                        qDebug() << "Versuche zu laden:" << _piece_image['B'];
                        qDebug() << "Existiert:" << _piece_image['B'];
                        qDebug() << "Geladen:" << !pixmap.isNull();
                        qDebug() << "Geladen:" << !pixmap.isNull();


                    }

                } else if ( piece->second == 'k' ) {

                    QPixmap pixmap(_piece_image['k']);
                    if ( !pixmap.isNull()) {
                        painter->drawPixmap(rect.topLeft(), pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio,
                                                                          Qt::SmoothTransformation));

                    } else {
                        qDebug() << "Versuche zu laden:" << _piece_image['k'];
                        qDebug() << "Existiert:" << _piece_image['k'];
                        qDebug() << "Geladen:" << !pixmap.isNull();
                        qDebug() << "Geladen:" << !pixmap.isNull();


                    }

                } else if ( piece->second == 'K' ) {

                    QPixmap pixmap(_piece_image['K']);
                    if ( !pixmap.isNull()) {
                        painter->drawPixmap(rect.topLeft(), pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio,
                                                                          Qt::SmoothTransformation));

                    } else {
                        qDebug() << "Versuche zu laden:" << _piece_image['K'];
                        qDebug() << "Existiert:" << _piece_image['K'];
                        qDebug() << "Geladen:" << !pixmap.isNull();
                        qDebug() << "Geladen:" << !pixmap.isNull();


                    }

                } else if ( piece->second == 'q' ) {

                    QPixmap pixmap(_piece_image['q']);
                    if ( !pixmap.isNull()) {
                        painter->drawPixmap(rect.topLeft(), pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio,
                                                                          Qt::SmoothTransformation));

                    } else {
                        qDebug() << "Versuche zu laden:" << _piece_image['q'];
                        qDebug() << "Existiert:" << _piece_image['q'];
                        qDebug() << "Geladen:" << !pixmap.isNull();
                        qDebug() << "Geladen:" << !pixmap.isNull();
                    }

                } else if ( piece->second == 'Q' ) {

                    QPixmap pixmap(_piece_image['Q']);
                    if ( !pixmap.isNull()) {
                        painter->drawPixmap(rect.topLeft(), pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio,
                                                                          Qt::SmoothTransformation));

                    } else {
                        qDebug() << "Versuche zu laden:" << _piece_image['Q'];
                        qDebug() << "Existiert:" << _piece_image['Q'];
                        qDebug() << "Geladen:" << !pixmap.isNull();
                        qDebug() << "Geladen:" << !pixmap.isNull();


                    }

                }


            }


        }
    }
    if ( _board._promotion ) {
        //wenn ein pawn am promotionsquare ist sollen möglichkeiten angezeigt werden die die promotion anzeigen
        drawPromotionChoices(painter, cellSize);
    }

}


void GameWidget::drawHighlights(QPainter *painter) {

    int cellSize = (width() - 400) / GameBoard::SIZE;
    QColor highlightColor(255, 255, 0, 128); // Gelb mit Transparenz
//highlighted die möglichen Züge
    for ( Pos position: _highlighted_positions ) {
        int col = position.get_col() - 1;
        int row = GameBoard::SIZE - position.get_row();
        QRect highlightRect(col * cellSize, row * cellSize, cellSize, cellSize);
        painter->fillRect(highlightRect, highlightColor);

        qDebug() << "Highlight auf Zelle: (" << col << "," << row << ")";
    }
}


void GameWidget::drawPromotionChoices(QPainter *painter, int cellSize) {
    int promotionRow = 0; // Obere Zeile (wie Brettzeile 8 von oben gesehen)
    QColor light(Qt::red); // Mach sie deutlich sichtbar

    for ( int i = 0; i < 4; ++i ) {
        //wird in current board gespeichert also die figuren zu den man promoten kann
        int col = GameBoard::SIZE + i; // also 8 + i → 9, 10, 11, 12

        QRect rect(col * cellSize, promotionRow * cellSize, cellSize, cellSize);
        painter->drawRect(rect);
        painter->fillRect(rect, light);

        auto piece = _board._current_board.find({col + 1, 8});//muss eins weiter nach links da dort die figuren sind
        if ( piece != _board._current_board.end()) {
            char fig = piece->second;
            QPixmap pixmap(_piece_image[fig]);
            if ( !pixmap.isNull()) {
                painter->drawPixmap(
                        rect.topLeft(),
                        pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)
                );
            } else {
                qDebug() << "Fehler beim Laden von Promotion-Bild für:" << fig;
            }
        }
    }
}


void GameWidget::mousePressEvent(QMouseEvent *event) {
    int cellSize = (width() - 400) / GameBoard::SIZE;
    int col = event->pos().x() / cellSize;
    int row = event->pos().y() / cellSize;

    //Umrechnung da die gedrückten felder nicht die logischen felder aus dem spiel sind
    int chessRow = GameBoard::SIZE - row;
    int chessCol = col + 1;

//Validierung ob einer der gedrückten felder überhaupt auf dem board waren damit man in den logik datein darauf acheten muss
    if ( row >= 0 && row < GameBoard::SIZE && col >= 0 && col < GameBoard::SIZE && !_board._promotion ) {
        qDebug() << "Geklickt auf Zelle: (" << chessCol << "," << chessRow << ")";
        qDebug() << "Wirkliche Zelle: (" << col << "," << row << ")";

        if ( _highlighted_positions.empty()) {
            // Erster Klick von einer Figur
            std::vector<Pos> pos = _board.get_possible_moves(chessRow, chessCol);

            if ( !pos.empty()) {
                //figur hat mögliche Züge
                _highlighted_positions = pos;
                before_pos.set(chessCol, chessRow);

            } else {
                //sonst nichts makieren

                _highlighted_positions.clear();
            }
        } else {
            // Zweiter Klick also die möglichen Züge der Figur
            auto it = std::find(_highlighted_positions.begin(), _highlighted_positions.end(), Pos(chessCol, chessRow));

            if ( it != _highlighted_positions.end()) {
                //erlaubtes feld also zug machen
                _board.set_cell(before_pos.get_col(), before_pos.get_row(), chessCol, chessRow);

            }

            //ich muss noch eine bool funktion machen die das schaut
            _board.check_pawn_promotion(); //hier wird board._promotion auf true gesetzt
            if ( _board._promotion ) {
                before_pos.set(chessCol, chessRow);
            }
            //das setzt das auf true, vielleicht noch eine eigene funktion machen wo man dann den vektor zurück gibt

            //nach zweitem klick die makierung löschen
            _highlighted_positions.clear();
        }


        if ( _board._message == "gewonnen" ) {
            QString winner = _board.check_turn() == 'w' ? "Black won" : "White won";  // weil Zug gerade gemacht wurde
            auto *dialog = new GameEndDialog(winner, "", this);

            connect(dialog, &GameEndDialog::playAgainClicked, this, [=]() {
                _board.reset();
                _highlighted_positions.clear();
                update();
                dialog->close();
            });

            connect(dialog, &GameEndDialog::exitClicked, this, []() {
                QApplication::quit();
            });

            dialog->exec();
        } else if ( _board._message == "unentschieden" ) {
            QString result = QString::fromStdString(
                    _board._message); //man könnte hier noch hinzufügen um was für ein draw es sich handelt,aber hab ich noch nicht gemacht

            auto *dialog = new GameEndDialog("Draw", result, this);

            connect(dialog, &GameEndDialog::playAgainClicked, this, [=]() {
                _board.reset();
                _highlighted_positions.clear();
                update();
                dialog->close();
            });

            connect(dialog, &GameEndDialog::exitClicked, this, []() {
                QApplication::quit();
            });

            dialog->exec();
        }

        //malt das Feld neu
        update();


    } else if ( _board._promotion ) {
        //sonderfall wenn ein pawn am promotion feld ist
        //dann muss man die möglichkeit haben die jeweiligen sachen anzuklicken
        _highlighted_positions.emplace_back(9, 8);
        _highlighted_positions.emplace_back(10, 8);
        _highlighted_positions.emplace_back(11, 8);
        _highlighted_positions.emplace_back(12, 8);
        auto it = std::find(_highlighted_positions.begin(), _highlighted_positions.end(), Pos(chessCol, chessRow));

        if ( it != _highlighted_positions.end()) {
            //erlaubtes feld also zug machen

            _board.set_cell(before_pos.get_col(), before_pos.get_row(), chessCol, chessRow);
            _board._promotion = false;
            _highlighted_positions.clear();

        }
        //malt das Feld neu
        update();

    }

}


