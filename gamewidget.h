//
// Created by Jenush on 06.06.2025.
//

#ifndef SCHACH_QT_GAMEWIDGET_H
#define SCHACH_QT_GAMEWIDGET_H



#include <QWidget>
#include "gameboard.h"
#include <map>

//dialoge haben andere namensgebung für klassen damit man die mit der schachlogik unterscheiden kann
class GameWidget : public QWidget {
Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void drawHighlights(QPainter *painter);
    void drawBoard(QPainter *painter);
    void drawPromotionChoices(QPainter *painter, int cellSize);
    void mousePressEvent(QMouseEvent *event) override;


private:
    //man muss sich merken was im vorfeld gedrückt wurde
    Pos before_pos;
    GameBoard _board;
    std::map<char, QString> _piece_image;
    std::vector<Pos> _highlighted_positions;
};


#endif //SCHACH_QT_GAMEWIDGET_H
