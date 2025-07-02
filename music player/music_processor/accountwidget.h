#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class accountwidget : public QWidget{
    Q_OBJECT

public:
    explicit accountwidget(QWidget *parent = nullptr);

signals:
    void loggedin(const QString &username, const QStringList &favoritePaths);
    void accountcreated();
    void loginfailed(const QString &reason);
    void passwordresetsuccess();
private slots:
    void onsigninbuttonclicked();
    void onloginbuttonclicked();
    void onforgotpasswordclicked();
private:
    QTabWidget *accountTabs;
    QLineEdit *signinusernamelineedit;
    QLineEdit *signinpasswordlineedit;
    QLineEdit *signinbestfriendnamelineedit;
    QPushButton *signinbutton;
    QLabel *signinstatuslabel;
    QLineEdit *loginusernamelineedit;
    QLineEdit *loginpasswordlineedit;
    QPushButton *loginbutton;
    QPushButton *forgotpasswordbutton;
    QLabel *loginstatuslabel;
    const QString accountfilepath = "D:/account.txt";
    const QString globalfavoritesfilepath = "D:/favorites.txt";
    bool accountline(const QString &line, QString &username, QString &password, QString &bestfriendname, QStringList &favoritepaths);
    bool finduser(const QString &usernametofind, QString &foundpassword, QString &foundbestfriendname, QStringList &foundfavoritepaths);
};

#endif
