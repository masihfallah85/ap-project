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
    bool isshuffleon;
    bool isshuffleon_fav;
    repeatstate currentrepeatstate;
    repeatstate repeatstate_fav;
    QListWidget *favoritelist;
    QPushButton *addtofavoritebutton;
    QString favoritesfilepath = "D:/favorites.txt";
    QTabWidget *tabs;
    QPushButton *fav_playbutton, *fav_pausebutton, *fav_stopbutton;
    QPushButton *fav_nextbutton, *fav_previousbutton, *fav_repeatbutton;
    QPushButton *fav_shufflebutton;
    QSlider *fav_slider;
    QListWidget *tempfavoritelist;
    QPushButton *temp_addbutton;
    QPushButton *temp_playbutton, *temp_pausebutton, *temp_stopbutton;
    QPushButton *temp_nextbutton, *temp_previousbutton;
    QPushButton *temp_repeatbutton, *temp_shufflebutton;
    QSlider *temp_slider;
    bool isshuffleon_temp;
    repeatstate repeatstate_temp;
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
    void playselectedfavoritesongfromcontrols();
    void playnextfavoritesong();
    void playpreviousfavoritesong();
    void fav_changerepeatstate();
    void fav_shufflestate();
    void savetotempfavorites();
    void playselectedtempfavoritesong();
    void playnexttempfavoritesong();
    void playprevioustempfavoritesong();
    void temp_changerepeatstate();
    void temp_shufflestate();
    void handletempplaybutton();
};
#endif
