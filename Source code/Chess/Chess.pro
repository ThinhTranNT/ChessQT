QT  += core gui
QT  += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameSaver.cpp \
    Move.cpp \
    Piece.cpp \
    Bishop.cpp \
    Board.cpp \
    King.cpp \
    Knight.cpp \
    Pawn.cpp \
    Player.cpp \
    PromotionDialog.cpp \
    Queen.cpp \
    Rook.cpp \
    SoundController.cpp \
    Spot.cpp \
    Game.cpp \
    lobby.cpp \
    main.cpp

HEADERS += \
    GameSaver.h \
    Move.h \
    Piece.h \
    Bishop.h \
    Board.h \
    Game.h \
    King.h \
    Knight.h \
    Pawn.h \
    Player.h \
    PromotionDialog.h \
    Queen.h \
    Rook.h \
    SoundController.h \
    Spot.h \
    lobby.h

FORMS += \
    Game.ui \
    PromotionDialog.ui \
    lobby.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Materials.qrc


