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
    repeatstate_temp = norepeat;
    isshuffleon_temp = false;
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
    mainvolumeslider = new QSlider(Qt::Vertical, this);
    mainvolumeslider->setRange(0, 100);
    mainvolumeslider->setValue(50);
    mainvolumeslider->setToolTip("volume");
    favvolumeslider = new QSlider(Qt::Vertical, this);
    favvolumeslider->setRange(0, 100);
    favvolumeslider->setValue(50);
    favvolumeslider->setToolTip("volume");
    tempvolumeslider = new QSlider(Qt::Vertical, this);
    tempvolumeslider->setRange(0, 100);
    tempvolumeslider->setValue(50);
    tempvolumeslider->setToolTip("volume");
    //layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    tabs = new QTabWidget(this);
    QWidget *mainTab = new QWidget(this);
    QHBoxLayout *mainTabhorizontalLayout = new QHBoxLayout();
    QVBoxLayout *mainTabLayout = new QVBoxLayout();
    QHBoxLayout *controls = new QHBoxLayout();
    controls->addWidget(shufflebutton);
    controls->addWidget(previousbutton);
    controls->addWidget(playbutton);
    controls->addWidget(pausebutton);
    controls->addWidget(stopbutton);
    controls->addWidget(nextbutton);
    controls->addWidget(repeatbutton);
    addtofavoritebutton = new QPushButton("save", this);
    temp_addbutton = new QPushButton("save to temp", this);
    mainTabLayout->addWidget(new QLabel("songs", this));
    mainTabLayout->addWidget(songlist);
    mainTabLayout->addWidget(addtofavoritebutton);
    mainTabLayout->addWidget(temp_addbutton);
    mainTabLayout->addWidget(currentsonglabel);
    mainTabLayout->addWidget(positionslider);
    mainTabLayout->addLayout(controls);
    mainTabhorizontalLayout->addLayout(mainTabLayout);
    mainTabhorizontalLayout->addWidget(mainvolumeslider);
    mainTab->setLayout(mainTabhorizontalLayout);
    tabs->addTab(mainTab, "Main");
    QWidget *favoritesTab = new QWidget(this);
    QHBoxLayout *favoritesTabhorizontalLayout = new QHBoxLayout();
    QVBoxLayout *favoritesLayout = new QVBoxLayout();
    favoritelist = new QListWidget(this);
    favoritesLayout->addWidget(new QLabel("favorite songs", this));
    favoritesLayout->addWidget(favoritelist);
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
    favoritesTabhorizontalLayout->addLayout(favoritesLayout);
    favoritesTabhorizontalLayout->addWidget(favvolumeslider);
    favoritesTab->setLayout(favoritesTabhorizontalLayout);
    tabs->addTab(favoritesTab, "favorites");
    QWidget *tempTab = new QWidget(this);
    QHBoxLayout *tempTabhorizontalLayout = new QHBoxLayout();
    QVBoxLayout *tempLayout = new QVBoxLayout();
    tempfavoritelist = new QListWidget(this);
    temp_slider = new QSlider(Qt::Horizontal, this);
    QHBoxLayout *temp_controls = new QHBoxLayout();
    temp_shufflebutton = new QPushButton("shuffle: off", this);
    temp_previousbutton = new QPushButton("previous", this);
    temp_playbutton = new QPushButton("play", this);
    temp_pausebutton = new QPushButton("pause", this);
    temp_stopbutton = new QPushButton("stop", this);
    temp_nextbutton = new QPushButton("next", this);
    temp_repeatbutton = new QPushButton("repeat: no", this);
    temp_controls->addWidget(temp_shufflebutton);
    temp_controls->addWidget(temp_previousbutton);
    temp_controls->addWidget(temp_playbutton);
    temp_controls->addWidget(temp_pausebutton);
    temp_controls->addWidget(temp_stopbutton);
    temp_controls->addWidget(temp_nextbutton);
    temp_controls->addWidget(temp_repeatbutton);
    tempLayout->addWidget(new QLabel("temporary list", this));
    tempLayout->addWidget(tempfavoritelist);
    tempLayout->addWidget(temp_slider);
    tempLayout->addLayout(temp_controls);
    tempTabhorizontalLayout->addLayout(tempLayout);
    tempTabhorizontalLayout->addWidget(tempvolumeslider);
    tempTab->setLayout(tempTabhorizontalLayout);
    tabs->addTab(tempTab, "temporary saves");
    tempLayout->addLayout(temp_controls);
    mainLayout->addWidget(tabs);
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
    connect(player, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status) {
        if (status != QMediaPlayer::EndOfMedia){
            return;
        }
        int currentTab = tabs->currentIndex();
        if (currentTab == 0) {
            if (currentrepeatstate == repeatone) {
                playselectedsongfromlist();
            }else if (isshuffleon) {
                playrandomsong();
            }else {
                switch (currentrepeatstate) {
                case repeatall:
                    playnextsong();
                    break;
                case norepeat:
                default:
                    player->stop();
                    currentsonglabel->setText("none");
                    positionslider->setValue(0);
                    break;
                }
            }
        }
        else if (currentTab == 1) {
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
                case norepeat:
                default:
                    player->stop();
                    currentsonglabel->setText("none");
                    fav_slider->setValue(0);
                    break;
                }
            }
        }

        else if (currentTab == 2) {
            if (repeatstate_temp == repeatone) {
                playselectedtempfavoritesong();
            } else if (isshuffleon_temp) {
                int count = tempfavoritelist->count();
                if (count > 0) {
                    int randindex = QRandomGenerator::global()->bounded(count);
                    tempfavoritelist->setCurrentRow(randindex);
                    playselectedtempfavoritesong();
                }
            } else {
                switch (repeatstate_temp) {
                case repeatall:
                    playnexttempfavoritesong();
                    break;
                case norepeat:
                default:
                    player->stop();
                    currentsonglabel->setText("none");
                    temp_slider->setValue(0);
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
    connect(temp_addbutton, &QPushButton::clicked, this, &musicplayer::savetotempfavorites);
    connect(tempfavoritelist, &QListWidget::itemDoubleClicked, this, &musicplayer::playselectedtempfavoritesong);
    connect(temp_playbutton, &QPushButton::clicked, this, &musicplayer::handletempplaybutton);
    connect(temp_pausebutton, &QPushButton::clicked, player, &QMediaPlayer::pause);
    connect(temp_stopbutton, &QPushButton::clicked, player, &QMediaPlayer::stop);
    connect(temp_nextbutton, &QPushButton::clicked, this, &musicplayer::playnexttempfavoritesong);
    connect(temp_previousbutton, &QPushButton::clicked, this, &musicplayer::playprevioustempfavoritesong);
    connect(temp_repeatbutton, &QPushButton::clicked, this, &musicplayer::temp_changerepeatstate);
    connect(temp_shufflebutton, &QPushButton::clicked, this, &musicplayer::temp_shufflestate);
    connect(player, &QMediaPlayer::positionChanged, this, &musicplayer::updateslider);
    connect(player, &QMediaPlayer::durationChanged, this, &musicplayer::setsliderrange);
    connect(temp_slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);
    connect(temp_slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);
    connect(mainvolumeslider, &QSlider::valueChanged, this, &musicplayer::setvolume);
    connect(favvolumeslider, &QSlider::valueChanged, this, &musicplayer::setvolume);
    connect(tempvolumeslider, &QSlider::valueChanged, this, &musicplayer::setvolume);
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
    if (!temp_slider->isSliderDown()) {
        temp_slider->setValue(position);
    }
}
//zaman music ro slider
void musicplayer::setsliderrange(qint64 duration) {
    positionslider->setRange(0, duration);
    fav_slider->setRange(0, duration);
    temp_slider->setRange(0, duration);
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
void musicplayer::savetotempfavorites() {
    QListWidgetItem *item = songlist->currentItem();
    if (!item){
        return;
    }
    QString filePath = item->data(Qt::UserRole).toString();
    if (filePath.isEmpty()){
        filePath = "D:/Musics/" + item->text();
    }
    QListWidgetItem *newitem = new QListWidgetItem(item->text());
    newitem->setData(Qt::UserRole, filePath);
    tempfavoritelist->addItem(newitem);
}
void musicplayer::playselectedtempfavoritesong() {
    QListWidgetItem *item = tempfavoritelist->currentItem();
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
void musicplayer::playnexttempfavoritesong() {
    int index = tempfavoritelist->currentRow();
    int next = index + 1;
    if (next < tempfavoritelist->count()) {
        tempfavoritelist->setCurrentRow(next);
        playselectedtempfavoritesong();
    } else if (tempfavoritelist->count() > 0) {
        tempfavoritelist->setCurrentRow(0);
        playselectedtempfavoritesong();
    }
}
void musicplayer::playprevioustempfavoritesong() {
    int index = tempfavoritelist->currentRow();
    int prev = index - 1;
    if (prev >= 0) {
        tempfavoritelist->setCurrentRow(prev);
        playselectedtempfavoritesong();
    } else if (tempfavoritelist->count() > 0) {
        tempfavoritelist->setCurrentRow(tempfavoritelist->count() - 1);
        playselectedtempfavoritesong();
    }
}
void musicplayer::temp_changerepeatstate() {
    switch (repeatstate_temp) {
    case norepeat:
        repeatstate_temp = repeatone;
        temp_repeatbutton->setText("repeat: 1");
        break;
    case repeatone:
        repeatstate_temp = repeatall;
        temp_repeatbutton->setText("repeat: all");
        break;
    case repeatall:
        repeatstate_temp = norepeat;
        temp_repeatbutton->setText("repeat: no");
        break;
    }
}
void musicplayer::temp_shufflestate() {
    isshuffleon_temp = !isshuffleon_temp;
    QString text = isshuffleon_temp ? "shuffle: on" : "shuffle: off";
    temp_shufflebutton->setText(text);
}
void musicplayer::handletempplaybutton() {
    if (player->playbackState() == QMediaPlayer::PausedState) {
        player->play();
    } else {
        playselectedtempfavoritesong();
    }
}
void musicplayer::setvolume(int volume) {
    audiooutput->setVolume(volume / 100.0f);
    if (sender() != mainvolumeslider) {
        mainvolumeslider->setValue(volume);
    }
    if (sender() != favvolumeslider) {
        favvolumeslider->setValue(volume);
    }
    if (sender() != tempvolumeslider) {
        tempvolumeslider->setValue(volume);
    }
}
void musicplayer::loaduserfavoriteslist(const QStringList &favoritepaths) {
    for (const QString &filePath : favoritepaths) {
        QFileInfo info(filePath);
        if (info.exists()) {
            QListWidgetItem *item = new QListWidgetItem(info.fileName());
            item->setData(Qt::UserRole, filePath);
            favoritelist->addItem(item);
        } else {
            qDebug() << "favorite file not found during user favorites load: " << filePath;
        }
    }
}
