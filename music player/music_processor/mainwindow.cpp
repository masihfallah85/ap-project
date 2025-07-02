#include "mainwindow.h"
#include <QVBoxLayout>
#include <QDebug>
mainwindow::mainwindow(QWidget *parent): QMainWindow(parent){
    stackedwidget = new QStackedWidget(this);
    setCentralWidget(stackedwidget);
    accountwidget_v = new accountwidget(this);
    stackedwidget->addWidget(accountwidget_v);
    connect(accountwidget_v, &accountwidget::loggedin, this, &mainwindow::onloggedin);
    connect(accountwidget_v, &accountwidget::accountcreated, this, &mainwindow::onaccountcreated);
    connect(accountwidget_v, &accountwidget::loginfailed, this, &mainwindow::onloginfailed);
    connect(accountwidget_v, &accountwidget::passwordresetsuccess, this, &mainwindow::onpasswordresetsuccess);
    musicplayerwidget = musicplayer::getinstance();
    stackedwidget->addWidget(musicplayerwidget);
    stackedwidget->setCurrentWidget(accountwidget_v);
    setWindowTitle("music player - account access");
    resize(800, 600);
}

mainwindow::~mainwindow(){
}
void mainwindow::onloggedin(const QString &username, const QStringList &favoritepaths)
{
    stackedwidget->setCurrentWidget(musicplayerwidget);
    setWindowTitle("Music Player - Logged in as " + username);
    musicplayerwidget->loaduserfavoriteslist(favoritepaths);
    QMessageBox::information(this, "Welcome!", "login successful as " + username + "!");
}
void mainwindow::onaccountcreated()
{
    qDebug() << "account created signal received by mainwindow.";
}

void mainwindow::onloginfailed(const QString &reason)
{
    qDebug() << "login failed signal received by mainwindow: " << reason;
}

void mainwindow::onpasswordresetsuccess()
{
    qDebug() << "password reset success signal received by mainwindow.";
}
