#ifndef MUSICPROCESSOR_H
#define MUSICPROCESSOR_H
#include <QWidget>
#include <QAudioDevice>
//bejaye incldue kardan bagyeh classha
QT_BEGIN_NAMESPACE
class QListWidget;
class QPushButton;
class QSlider;
class QLabel;
class QMediaPlayer;
class QAudioOutput;
class QTabWidget;
QT_END_NAMESPACE

//class pardazesh music
class musicplayer : public QWidget {
    Q_OBJECT

public:
    //singelton kardan
    static musicplayer* getinstance();
    enum repeatstate {norepeat,repeatone,repeatall};
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
    QPushButton *repeatbutton;
    QMediaPlayer *player;
    QAudioOutput *audiooutput;
    QPushButton *shufflebutton;
    repeatstate currentrepeatstate;
    bool isshuffleon;
    QListWidget *favoritelist;
    QPushButton *addtofavoritebutton;
    QString favoritesfilepath = "favorites.txt";
    QTabWidget *tabs;
private slots:
    void playselectedsong();
    void updateslider(qint64 position);
    void setsliderrange(qint64 duration);
    void handleplaybutton();
    void playselectedsongfromlist();
    void playnextsong();
    void playprevioussong();
    void changerepeatstate();
    void shufflestate();
    void playrandomsong();
    void savecurrentsongtofavorites();
    void loadfavoritesfromfile();
    void playselectedfavoritesong();
};
#endif
