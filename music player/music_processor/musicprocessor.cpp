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
#include <QRandomGenerator>
#include <QTabWidget>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
//singeton
musicplayer* musicplayer::instance = nullptr;
//coonstruor
musicplayer::musicplayer(QWidget *parent) : QWidget(parent) {
    //ui objects intiliazations
    currentrepeatstate = norepeat;
    repeatstate_fav = norepeat;
    isshuffleon = false;
    isshuffleon_fav = false;
    songlist = new QListWidget(this);
    playbutton = new QPushButton("play", this);
    pausebutton = new QPushButton("pause", this);
    stopbutton = new QPushButton("stop", this);
    positionslider = new QSlider(Qt::Horizontal, this);
    currentsonglabel = new QLabel("none", this);
    nextbutton = new QPushButton("next", this);
    previousbutton = new QPushButton("prevoius", this);
    repeatbutton = new QPushButton("repeat: no", this);
    shufflebutton = new QPushButton("shuffle: off", this);
    //audioplayer inialziation
    player = new QMediaPlayer(this);
    audiooutput = new QAudioOutput(this);
    player->setAudioOutput(audiooutput);
    //layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    tabs = new QTabWidget(this);

    // ---------- Main Tab ----------
    QWidget *mainTab = new QWidget(this);
    QVBoxLayout *mainTabLayout = new QVBoxLayout(mainTab);
    QHBoxLayout *controls = new QHBoxLayout();
    controls->addWidget(shufflebutton);
    controls->addWidget(previousbutton);
    controls->addWidget(playbutton);
    controls->addWidget(pausebutton);
    controls->addWidget(stopbutton);
    controls->addWidget(nextbutton);
    controls->addWidget(repeatbutton);
    addtofavoritebutton = new QPushButton("save", this);
    mainTabLayout->addWidget(new QLabel("songs", this));
    mainTabLayout->addWidget(songlist);
    mainTabLayout->addWidget(addtofavoritebutton);
    mainTabLayout->addWidget(currentsonglabel);
    mainTabLayout->addWidget(positionslider);
    mainTabLayout->addLayout(controls);
    mainTab->setLayout(mainTabLayout);
    tabs->addTab(mainTab, "Main");
    QWidget *favoritesTab = new QWidget(this);
    QVBoxLayout *favoritesLayout = new QVBoxLayout(favoritesTab);
    favoritelist = new QListWidget(this);
    favoritesLayout->addWidget(new QLabel("favorite songs", this));
    favoritesLayout->addWidget(favoritelist);
    // Control buttons for Favorites tab
    QHBoxLayout *fav_controls = new QHBoxLayout();
    fav_shufflebutton = new QPushButton("shuffle: off", this);
    fav_previousbutton = new QPushButton("previous", this);
    fav_playbutton = new QPushButton("play", this);
    fav_pausebutton = new QPushButton("pause", this);
    fav_stopbutton = new QPushButton("stop", this);
    fav_nextbutton = new QPushButton("next", this);
    fav_repeatbutton = new QPushButton("repeat: no", this);
    fav_slider = new QSlider(Qt::Horizontal, this);
    fav_controls->addWidget(fav_shufflebutton);
    fav_controls->addWidget(fav_previousbutton);
    fav_controls->addWidget(fav_playbutton);
    fav_controls->addWidget(fav_pausebutton);
    fav_controls->addWidget(fav_stopbutton);
    fav_controls->addWidget(fav_nextbutton);
    fav_controls->addWidget(fav_repeatbutton);
    favoritesLayout->addWidget(fav_slider);
    favoritesLayout->addLayout(fav_controls);
    favoritesTab->setLayout(favoritesLayout);
    tabs->addTab(favoritesTab, "Favorites");
    mainLayout->addWidget(tabs);
    setLayout(mainLayout);
    //load songs to list8
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
    connect(player, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status) {
        if (status != QMediaPlayer::EndOfMedia) return;
        int currentTab = tabs->currentIndex();
        if (currentTab == 0) {
            if (currentrepeatstate == repeatone) {
                playselectedsongfromlist();
            } else if (isshuffleon) {
                playrandomsong();
            } else {
                switch (currentrepeatstate) {
                case repeatall:
                    playnextsong();
                    break;
                default:
                    player->stop();
                    currentsonglabel->setText("none");
                    positionslider->setValue(0);
                    break;
                }
            }
        } else {
            if (repeatstate_fav == repeatone) {
                playselectedfavoritesongfromcontrols();
            } else if (isshuffleon_fav) {
                int count = favoritelist->count();
                if (count > 0) {
                    int randindex = QRandomGenerator::global()->bounded(count);
                    favoritelist->setCurrentRow(randindex);
                    playselectedfavoritesongfromcontrols();
                }
            } else {
                switch (repeatstate_fav) {
                case repeatall:
                    playnextfavoritesong();
                    break;
                default:
                    player->stop();
                    currentsonglabel->setText("none");
                    fav_slider->setValue(0);
                    break;
                }
            }
        }
    });
    connect(repeatbutton, &QPushButton::clicked, this, &musicplayer::changerepeatstate);
    connect(shufflebutton, &QPushButton::clicked, this, &musicplayer::shufflestate);
    connect(addtofavoritebutton, &QPushButton::clicked, this, &musicplayer::savecurrentsongtofavorites);
    connect(favoritelist, &QListWidget::itemDoubleClicked, this, &musicplayer::playselectedfavoritesong);
    connect(fav_playbutton, &QPushButton::clicked, this, &musicplayer::playselectedfavoritesongfromcontrols);
    connect(fav_pausebutton, &QPushButton::clicked, player, &QMediaPlayer::pause);
    connect(fav_stopbutton, &QPushButton::clicked, player, &QMediaPlayer::stop);
    connect(fav_previousbutton, &QPushButton::clicked, this, &musicplayer::playpreviousfavoritesong);
    connect(fav_nextbutton, &QPushButton::clicked, this, &musicplayer::playnextfavoritesong);
    connect(fav_shufflebutton, &QPushButton::clicked, this, &musicplayer::fav_shufflestate);
    connect(fav_repeatbutton, &QPushButton::clicked, this, &musicplayer::fav_changerepeatstate);
    connect(player, &QMediaPlayer::positionChanged, this, &musicplayer::updateslider);
    connect(player, &QMediaPlayer::durationChanged, this, &musicplayer::setsliderrange);
    connect(fav_slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);
    //bargozary monakhaba
    loadfavoritesfromfile();
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
    if (!fav_slider->isSliderDown()) {
        fav_slider->setValue(position);
    }
}
//zaman music ro slider
void musicplayer::setsliderrange(qint64 duration) {
    positionslider->setRange(0, duration);
    fav_slider->setRange(0, duration);
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
//taghir halat tekrar
void musicplayer::changerepeatstate() {
    switch (currentrepeatstate) {
    case norepeat:
        currentrepeatstate = repeatone;
        repeatbutton->setText("repeat: 1");
        break;
    case repeatone:
        currentrepeatstate = repeatall;
        repeatbutton->setText("repeat: all");
        break;
    case repeatall:
        currentrepeatstate = norepeat;
        repeatbutton->setText("repeat: no");
        break;
    }
}
//taghir halat shuffle
void musicplayer::shufflestate() {
    isshuffleon = !isshuffleon;
    if (isshuffleon) {
        shufflebutton->setText("shuffle: on");
    } else {
        shufflebutton->setText("shuffle: off");
    }
}
//pakhs random
void musicplayer::playrandomsong() {
    int songcount = songlist->count();
    if (songcount == 0) {
        player->stop();
        currentsonglabel->setText("none");
        positionslider->setValue(0);
        return;
    }
    int randomindex = QRandomGenerator::global()->bounded(songcount);
    songlist->setCurrentRow(randomindex);
    playselectedsongfromlist();
}
void musicplayer::savecurrentsongtofavorites() {
    QListWidgetItem *item = songlist->currentItem();
    QString filepath = item->data(Qt::UserRole).toString();
    if (filepath.isEmpty()) {
        filepath = "D:/Musics/" + item->text();
    }
    QFile file(favoritesfilepath);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << filepath << "\n";
        file.close();
        QListWidgetItem *favitem = new QListWidgetItem(item->text());
        favitem->setData(Qt::UserRole, filepath);
        favoritelist->addItem(favitem);
    }
}
void musicplayer::loadfavoritesfromfile() {
    QFile file(favoritesfilepath);
    if (!file.exists()){
        return;
    }
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            QFileInfo info(line);
            if (info.exists()) {
                QListWidgetItem *item = new QListWidgetItem(info.fileName());
                item->setData(Qt::UserRole, line);
                favoritelist->addItem(item);
            }
        }
        file.close();
    }
}
void musicplayer::playselectedfavoritesong() {
    QListWidgetItem *item = favoritelist->currentItem();
    if (!item){
        return;
    }
    QString filePath = item->data(Qt::UserRole).toString();
    if (!QFileInfo::exists(filePath)) {
        return;
    }
    player->setSource(QUrl::fromLocalFile(filePath));
    player->play();
    currentsonglabel->setText("playing: " + item->text());
}
void musicplayer::playselectedfavoritesongfromcontrols() {
    QListWidgetItem *item = favoritelist->currentItem();
    if (!item) {
        return;
    }
    QString filePath = item->data(Qt::UserRole).toString();
    if (filePath.isEmpty()) {
        filePath = "D:/Musics/" + item->text();
    }
    if (!QFileInfo::exists(filePath)) {
        return;
    }
    player->setSource(QUrl::fromLocalFile(filePath));
    player->play();
    currentsonglabel->setText("playing: " + item->text());
}
void musicplayer::playnextfavoritesong() {
    int currentindex = favoritelist->currentRow();
    int nextindex = currentindex + 1;
    if (nextindex < favoritelist->count()) {
        favoritelist->setCurrentRow(nextindex);
        playselectedfavoritesongfromcontrols();
    } else if (favoritelist->count() > 0) {
        favoritelist->setCurrentRow(0);
        playselectedfavoritesongfromcontrols();
    }
}
void musicplayer::playpreviousfavoritesong() {
    int currentindex = favoritelist->currentRow();
    int previousindex = currentindex - 1;
    if (previousindex >= 0) {
        favoritelist->setCurrentRow(previousindex);
        playselectedfavoritesongfromcontrols();
    } else if (favoritelist->count() > 0) {
        favoritelist->setCurrentRow(favoritelist->count() - 1);
        playselectedfavoritesongfromcontrols();
    }
}
void musicplayer::fav_changerepeatstate() {
    switch (repeatstate_fav) {
    case norepeat:
        repeatstate_fav = repeatone;
        fav_repeatbutton->setText("repeat: 1");
        break;
    case repeatone:
        repeatstate_fav = repeatall;
        fav_repeatbutton->setText("repeat: all");
        break;
    case repeatall:
        repeatstate_fav = norepeat;
        fav_repeatbutton->setText("repeat: no");
        break;
    }
}
void musicplayer::fav_shufflestate() {
    isshuffleon_fav = !isshuffleon_fav;
    QString text = isshuffleon_fav ? "shuffle: on" : "shuffle: off";
    fav_shufflebutton->setText(text);
}
