#include "musicprocessor.h"
#include <QPushButton>
#include <QSlider>
#include <QDebug>
#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDir>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QListWidgetItem>
#include <QFileInfo>
//singeton
musicplayer* musicplayer::instance = nullptr;
//coonstruor
musicplayer::musicplayer(QWidget *parent) : QWidget(parent) {
    //ui objects intiliazations
    songlist = new QListWidget(this);
    playbutton = new QPushButton("play", this);
    pausebutton = new QPushButton("pause", this);
    stopbutton = new QPushButton("stop", this);
    positionslider = new QSlider(Qt::Horizontal, this);
    currentsonglabel = new QLabel("none", this);
    nextbutton = new QPushButton("next", this);
    previousbutton = new QPushButton("prevoius", this);
    //audioplayer inialziation
    player = new QMediaPlayer(this);
    audiooutput = new QAudioOutput(this);
    player->setAudioOutput(audiooutput);
    //layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *controls = new QHBoxLayout();
    controls->addWidget(previousbutton);
    controls->addWidget(playbutton);
    controls->addWidget(pausebutton);
    controls->addWidget(stopbutton);
    controls->addWidget(nextbutton);
    mainLayout->addWidget(new QLabel("songs", this));
    mainLayout->addWidget(songlist);
    mainLayout->addWidget(currentsonglabel);
    mainLayout->addWidget(positionslider);
    mainLayout->addLayout(controls);
    setLayout(mainLayout);
    //load songs to list
    QDir musicDir("D:/Musics");
    if (!musicDir.exists()) {
        qDebug() << "Music directory does not exist!";
    }else{
        qDebug() << "music directory exist";
    }
    QStringList files = musicDir.entryList(QStringList() << "*.mp3" << "*.wav", QDir::Files);
    for (const QString &file : files) {
        QListWidgetItem *item = new QListWidgetItem(file);
        item->setData(Qt::UserRole, musicDir.absoluteFilePath(file));
        songlist->addItem(file);
        qDebug() << "found file: " << file;
    }
    //connect buttons to slots(fucntions)
    connect(playbutton, &QPushButton::clicked, this, &musicplayer::handleplaybutton);
    connect(pausebutton, &QPushButton::clicked, player, &QMediaPlayer::pause);
    connect(stopbutton, &QPushButton::clicked, player, &QMediaPlayer::stop);
    connect(songlist, &QListWidget::itemDoubleClicked, this, &musicplayer::playselectedsongfromlist);
    connect(player, &QMediaPlayer::positionChanged, this, &musicplayer::updateslider);
    connect(player, &QMediaPlayer::durationChanged, this, &musicplayer::setsliderrange);
    connect(positionslider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);
    connect(nextbutton, &QPushButton::clicked, this, &::musicplayer::playnextsong);
    connect(previousbutton, &QPushButton::clicked, this, &musicplayer::playprevioussong);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status){
        if (status == QMediaPlayer::EndOfMedia) {
            currentsonglabel->setText("none");
            positionslider->setValue(0);
        }
    });
}
//singleton
musicplayer* musicplayer::getinstance() {
    if (!instance) {
        instance = new musicplayer();
    }
    return instance;
}
//pakhs music
void musicplayer::playselectedsong() {
    QListWidgetItem *item = songlist->currentItem();
    if (!item) return;

    QString filePath = "D:/Musics/" + item->text();
    player->setSource(QUrl::fromLocalFile(filePath));
    player->play();
    currentsonglabel->setText("playing: " + item->text());
}
//avaz shodan slider
void musicplayer::updateslider(qint64 position) {
    if (!positionslider->isSliderDown()) {
        positionslider->setValue(position);
    }
}
//zaman music ro slider
void musicplayer::setsliderrange(qint64 duration) {
    positionslider->setRange(0, duration);
}
//handle dokmeha
void musicplayer::handleplaybutton() {
    if (player->playbackState() == QMediaPlayer::PausedState) {
        player->play();
        qDebug() << "Resuming play";
    } else {
        playselectedsongfromlist();
    }
}
//emtekhab o bakhs ahang
void musicplayer::playselectedsongfromlist() {
    QListWidgetItem *item = songlist->currentItem();
    if (!item) {
        qDebug() << "nothing chosen";
        return;
    }
    QString filePath = item->data(Qt::UserRole).toString();
    if (filePath.isEmpty()) {
        qDebug() << "item deosnt have path";
        filePath = "D:/Musics/" + item->text();
    }
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists()) {
        qDebug() << "file doenst exist at path: " << filePath;
        return;
    }
    qDebug() << "play song of " << filePath;
    player->setSource(QUrl::fromLocalFile(filePath));
    player->play();
    currentsonglabel->setText("playing: " + item->text());
}
//entekhab music ghably
void musicplayer::playprevioussong() {
    int currentindex = songlist->currentRow();
    int previousindex = currentindex - 1;
    if (previousindex >= 0) {
        songlist->setCurrentRow(previousindex);
        playselectedsongfromlist();
    } else {
        if (songlist->count() > 0) {
            songlist->setCurrentRow(songlist->count() - 1);
            playselectedsongfromlist();
        } else {
            player->stop();
            currentsonglabel->setText("none");
        }
    }
}
//entekhab music baady
void musicplayer::playnextsong() {
    int currentIndex = songlist->currentRow();
    int nextIndex = currentIndex + 1;
    if (nextIndex < songlist->count()) {
        songlist->setCurrentRow(nextIndex);
        playselectedsongfromlist();
    } else {
        if (songlist->count() > 0) {
            songlist->setCurrentRow(0);
            playselectedsongfromlist();
        } else {
            player->stop();
            currentsonglabel->setText("none");
        }
    }
}
