#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QStackedWidget>
#include <QMessageBox>

#include "accountwidget.h"
#include "musicprocessor.h"

class mainwindow : public QMainWindow{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow();

private slots:
    void onloggedin(const QString &username, const QStringList &favoritepaths);
    void onaccountcreated();
    void onloginfailed(const QString &reason);
    void onpasswordresetsuccess();

private:
    QStackedWidget *stackedwidget;
    accountwidget *accountwidget_v;
    musicplayer *musicplayerwidget;
};

#endif // MAINWINDOW_H
