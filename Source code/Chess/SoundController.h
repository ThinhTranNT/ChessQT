#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSoundEffect>

class SoundController
{
public:
    static QMediaPlayer* backgroundMusic;
    static QAudioOutput* audioBackground;
    static QMediaPlayer* moveSoundEffect;
    static QAudioOutput* audio;
    static bool isMute;
    static void setBackgroundMusic();
    static void deleteSoundController();
    static void playPieceMoveSoundEffect();
};

#endif // SOUNDCONTROLLER_H
