// mainwindow.cpp
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>


MainWindow::MainWindow() {
    auto *central = new QWidget;
    auto *layout = new QVBoxLayout;

    startButton = new QPushButton("Spielen");
    layout->addWidget(startButton);

    gameWidget = new GameWidget;
    gameWidget->hide(); // Anfangs versteckt
    layout->addWidget(gameWidget);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);

    central->setLayout(layout);
    setCentralWidget(central);
}


void MainWindow::startGame() {
    startButton->hide();
    gameWidget->show();
}
