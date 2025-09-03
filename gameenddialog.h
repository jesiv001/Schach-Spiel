//
// Created by Jenush on 08.07.2025.
//

#include "gameenddialog.h"

#include <QVBoxLayout>


GameEndDialog::GameEndDialog(const QString &resultText, const QString &reasonText, QWidget *parent)
        : QDialog(parent) {

    setWindowTitle("Game Over");
    setFixedSize(300, 200);

    _result_label = new QLabel(resultText);
    _result_label->setAlignment(Qt::AlignCenter);
    _result_label->setStyleSheet("font-weight: bold; font-size: 20px;");

    _reason_label = new QLabel(reasonText);
    _reason_label->setAlignment(Qt::AlignCenter);
    _reason_label->setStyleSheet("font-size: 14px; color: gray;");

    _play_again_button = new QPushButton("Nochmal spielen");
    _exit_button = new QPushButton("Beenden");

    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(_play_again_button);
    buttonLayout->addWidget(_exit_button);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(_result_label);
    if ( !reasonText.isEmpty())
        mainLayout->addWidget(_reason_label);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    connect(_play_again_button, &QPushButton::clicked, this, &GameEndDialog::playAgainClicked);
    connect(_exit_button, &QPushButton::clicked, this, &GameEndDialog::exitClicked);
}
