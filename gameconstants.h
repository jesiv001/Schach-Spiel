
//
// Created by Jenush on 15.07.2025.
//
#ifndef SCHACH_QT_GAMECONSTANTS_H
#define SCHACH_QT_GAMECONSTANTS_H
struct CHESS {
    static constexpr int COLMIN = 1;
    static constexpr int COLMAX = 8;
    static constexpr char ROWMIN = 1;
    static constexpr int ROWMAX = 8;
    static constexpr int ENPASSANTROWWHTE = 5;
    static constexpr int ENPASSANTCAPTUREROWWHTE = 6;
    static constexpr int ENPASSANTROWBLACK = 4;
    static constexpr int ENPASSANTCAPTURERBLACK = 3;
    static constexpr char WHITEPIECE[2] = {'A', 'Z'};
    static constexpr char BLACKPIECE[2] = {'a', 'z'};
    static constexpr char EMPTYSPACE = '-';
};
#endif //SCHACH_QT_GAMECONSTANTS_H
