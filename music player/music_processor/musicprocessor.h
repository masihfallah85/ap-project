#ifndef MUSICPROCESSOR_H
#define MUSICPROCESSOR_H
#include <QWidget>

//bejaye incldue kardan bagyeh classha
QT_BEGIN_NAMESPACE
class QListWidget;
class QPushButton;
class QSlider;
class QLabel;
class QMediaPlayer;
class QAudioOutput;
QT_END_NAMESPACE

//class pardazesh music
class musicplayer : public QWidget {
    Q_OBJECT

public:
    //singelton kardan
    static musicplayer* getinstance();
    musicplayer(const musicplayer&) = delete;
    musicplayer& operator=(const musicplayer&) = delete;

private:
    //cosntructor
    explicit musicplayer(QWidget *parent = nullptr);
    //singeton
    static musicplayer* instance;
    //agza
    QListWidget *songlist;
    QPushButton *playbutton, *pausebutton, *stopbutton;
    QSlider *positionslider;
    QLabel *currentsonglabel;
    QPushButton *nextbutton, *previousbutton;
    QMediaPlayer *player;
    QAudioOutput *audiooutput;

private slots:
    void playselectedsong();
    void updateslider(qint64 position);
    void setsliderrange(qint64 duration);
    void handleplaybutton();
    void playselectedsongfromlist();
    void playnextsong();
    void playprevioussong();
};
#endif
