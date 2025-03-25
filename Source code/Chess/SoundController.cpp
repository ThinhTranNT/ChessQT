#include "SoundController.h"

QMediaPlayer* SoundController::backgroundMusic = new QMediaPlayer();
QAudioOutput* SoundController::audioBackground = new QAudioOutput();
QMediaPlayer* SoundController::moveSoundEffect = new QMediaPlayer();
QAudioOutput* SoundController::audio = new QAudioOutput();
bool SoundController::isMute = false;

void SoundController::setBackgroundMusic()
{
    backgroundMusic->setAudioOutput(audioBackground);
    backgroundMusic->setSource(QUrl("qrc:/Soundtrack/BackgroundMusic.mp3"));
    audioBackground->setVolume(0.3f);
    backgroundMusic->setLoops(QMediaPlayer::Infinite);

    backgroundMusic->play();
}

void SoundController::playPieceMoveSoundEffect()
{
    if(isMute == true)
    {
        return;
    }
    delete moveSoundEffect;
    delete audio;
    moveSoundEffect = new QMediaPlayer();
    audio = new QAudioOutput();
    moveSoundEffect->setAudioOutput(audio);
    moveSoundEffect->setSource(QUrl("qrc:/Soundtrack/PieceMoveSoundEffect.mp3"));
    audio->setVolume(1);
    moveSoundEffect->play();

}

void SoundController::deleteSoundController()
{
    delete backgroundMusic;
    delete audioBackground;
    delete moveSoundEffect;
    delete audio;
    backgroundMusic = nullptr;
    audioBackground = nullptr;
    moveSoundEffect = nullptr;
    audio = nullptr;

}
