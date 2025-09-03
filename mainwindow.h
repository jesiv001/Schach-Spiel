// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QPushButton>
#include "gamewidget.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow();

private slots:
    void startGame();

private:
    QPushButton *startButton;
    GameWidget *gameWidget;
};

#endif
