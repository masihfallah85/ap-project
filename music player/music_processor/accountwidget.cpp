#include "accountwidget.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>
#include <QDebug>
accountwidget::accountwidget(QWidget *parent) : QWidget(parent){
    QDir dir("D:/");
    if (!dir.exists()) {
        qDebug() << "directory doesnt exist";
    }
    accountTabs = new QTabWidget(this);
    QWidget *signInTab = new QWidget(accountTabs);
    QVBoxLayout *signinLayout = new QVBoxLayout(signInTab);
    signinusernamelineedit = new QLineEdit(signInTab);
    signinusernamelineedit->setPlaceholderText("username");
    signinpasswordlineedit = new QLineEdit(signInTab);
    signinpasswordlineedit->setPlaceholderText("password");
    signinpasswordlineedit->setEchoMode(QLineEdit::Password);
    signinbestfriendnamelineedit = new QLineEdit(signInTab);
    signinbestfriendnamelineedit->setPlaceholderText("best friend's name (for password recovery)");
    signinbutton = new QPushButton("sign up", signInTab);
    signinstatuslabel = new QLabel("", signInTab);
    signinLayout->addWidget(new QLabel("create new account", signInTab));
    signinLayout->addWidget(signinusernamelineedit);
    signinLayout->addWidget(signinpasswordlineedit);
    signinLayout->addWidget(signinbestfriendnamelineedit);
    signinLayout->addWidget(signinbutton);
    signinLayout->addWidget(signinstatuslabel);
    signinLayout->addStretch();
    accountTabs->addTab(signInTab, "sign up");
    connect(signinbutton, &QPushButton::clicked, this, &accountwidget::onsigninbuttonclicked);
    QWidget *loginTab = new QWidget(accountTabs);
    QVBoxLayout *loginLayout = new QVBoxLayout(loginTab);
    loginusernamelineedit = new QLineEdit(loginTab);
    loginusernamelineedit->setPlaceholderText("username");
    loginpasswordlineedit = new QLineEdit(loginTab);
    loginpasswordlineedit->setPlaceholderText("password");
    loginpasswordlineedit->setEchoMode(QLineEdit::Password);
    loginbutton = new QPushButton("Login", loginTab);
    forgotpasswordbutton = new QPushButton("forgot password?", loginTab);
    loginstatuslabel = new QLabel("", loginTab);
    loginLayout->addWidget(new QLabel("log in to Your account", loginTab));
    loginLayout->addWidget(loginusernamelineedit);
    loginLayout->addWidget(loginpasswordlineedit);
    loginLayout->addWidget(loginbutton);
    loginLayout->addWidget(forgotpasswordbutton);
    loginLayout->addWidget(loginstatuslabel);
    loginLayout->addStretch();
    accountTabs->addTab(loginTab, "log in");
    connect(loginbutton, &QPushButton::clicked, this, &accountwidget::onloginbuttonclicked);
    connect(forgotpasswordbutton, &QPushButton::clicked, this, &accountwidget::onforgotpasswordclicked);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(accountTabs);
}
//sign in
void accountwidget::onsigninbuttonclicked(){
    QString username = signinusernamelineedit->text().trimmed();
    QString password = signinpasswordlineedit->text();
    QString bestfriendname = signinbestfriendnamelineedit->text().trimmed();
    if (username.isEmpty() || password.isEmpty() || bestfriendname.isEmpty()) {
        signinstatuslabel->setText("<font color='red'>All fields are required!</font>");
        return;
    }
    if (username.contains("::") || password.contains("::") || bestfriendname.contains("::")) {
        signinstatuslabel->setText("fFields cannot cntain ::");
        return;
    }
    QString dummyPass, dummybff;
    QStringList dummyfavs;
    if (finduser(username, dummyPass, dummybff, dummyfavs)) {
        signinstatuslabel->setText("Username already exists");
        return;
    }
    QFile accountfile(accountfilepath);
    if (accountfile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&accountfile);
        QStringList globalfavorites;
        QFile favfile(globalfavoritesfilepath);
        if (favfile.exists() && favfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&favfile);
            while (!in.atEnd()) {
                QString line = in.readLine().trimmed();
                if (!line.isEmpty()) {
                    globalfavorites.append(line);
                }
            }
            favfile.close();
        QString encodedfavorites = "";
        for (const QString &favpath : globalfavorites) {
            if (!encodedfavorites.isEmpty()){
                encodedfavorites += favpath;
                encodedfavorites += ";;";
            }
        }
        out << username << "::" << password << "::" << bestfriendname << "::" << encodedfavorites << "\n";
        accountfile.close();
        signinstatuslabel->setText("account created successfully!");
        QMessageBox::information(this, "account Created", "Your account has been created. You can now log in.");
        emit accountcreated();
        signinusernamelineedit->clear();
        signinpasswordlineedit->clear();
        signinbestfriendnamelineedit->clear();
        accountTabs->setCurrentIndex(1);
    } else {
        signinstatuslabel->setText("failed to create account. Cannot open file");
        QMessageBox::critical(this, "File Error","Could not open D:/account.txt for writing");
    }
}
}
//login
void accountwidget::onloginbuttonclicked(){
    QString username = loginusernamelineedit->text().trimmed();
    QString password = loginpasswordlineedit->text();
    if (username.isEmpty() || password.isEmpty()) {
        loginstatuslabel->setText("Username and password are required");
        return;
    }
    QString foundpassword;
    QString foundbestfriendname;
    QStringList favoritepaths;
    if (finduser(username, foundpassword, foundbestfriendname, favoritepaths)) {
        if (password == foundpassword) {
            loginstatuslabel->setText("login successful");
            emit loggedin(username, favoritepaths);
            loginusernamelineedit->clear();
            loginpasswordlineedit->clear();
        } else {
            loginstatuslabel->setText("failed to login");
            emit loginfailed("incorrect password.");
        }
    } else {
        loginstatuslabel->setText("failed to login");
        emit loginfailed("Username not found.");
    }
}
void accountwidget::onforgotpasswordclicked(){
    QString username = loginusernamelineedit->text().trimmed();
    if (username.isEmpty()) {
        QMessageBox::warning(this, "password recovery", "please enter your username in the login tab first.");
        return;
    }
    QString bestfriendnameinput = QInputDialog::getText(this, "password recovery","enter your best friend's name for user: " + username,QLineEdit::Normal);
    if (bestfriendnameinput.isEmpty()) {
        QMessageBox::warning(this, "password recovery", "best friend's name cannot be empty.");
        return;
    }
    QString foundpassword;
    QString foundbestfriendname;
    QStringList favoritepaths;
    if (finduser(username, foundpassword, foundbestfriendname, favoritepaths)) {
        if (bestfriendnameinput == foundbestfriendname) {
            QString newPassword = QInputDialog::getText(this, "reset Password", "best Friend name matched enter your new password:", QLineEdit::Password);
            if (newPassword.isEmpty()) {
                QMessageBox::warning(this, "reset password", "new password cannot be empty.");
                return;
            }
            if (newPassword.contains("::")) {
                QMessageBox::warning(this, "reset password", "new password cannot contain ::");
                return;
            }
            QFile accountfile(accountfilepath);
            if (!accountfile.open(QIODevice::ReadWrite | QIODevice::Text)) {
                return;
            }
            QTextStream in(&accountfile);
            QStringList lines;
            bool userFoundAndUpdated = false;
            while (!in.atEnd()) {
                QString line = in.readLine();
                QString currentUsername;
                QString currentPass, currentBFF;
                QStringList currentFavs;
                if (accountline(line, currentUsername, currentPass, currentBFF, currentFavs)) {
                    if (currentUsername == username) {
                        QString encodedfavorites = "";
                        for (const QString &favpath : currentFavs) {
                            if (!encodedfavorites.isEmpty()) {
                                encodedfavorites += ";;";
                            }
                           encodedfavorites += favpath;
                        }
                        lines.append(username + "::" + newPassword + "::" + currentBFF + "::" + encodedfavorites);
                        userFoundAndUpdated = true;
                    } else {
                        lines.append(line);
                    }
                } else {
                    lines.append(line);
                }
            }
            if (userFoundAndUpdated) {
                accountfile.resize(0);
                accountfile.seek(0);
                QTextStream out(&accountfile);
                for (const QString &line : lines) {
                    out << line << "\n";
                }
                accountfile.close();
                QMessageBox::information(this, "reset password", "Password has been successfully reset");
                emit passwordresetsuccess();
            } else {
                return;
            }

        } else {
            QMessageBox::warning(this, "password Recovery", "incorrect best friend name");
        }
    } else {
        QMessageBox::warning(this, "password recovery", "username not found.");
    }
}
bool accountwidget::accountline(const QString &line, QString &username, QString &password, QString &bestfriendname, QStringList &favoritepaths) {
    QStringList parts = line.split("::");
    if (parts.size() >= 3) {
        username = parts.at(0);
        password = parts.at(1);
        bestfriendname = parts.at(2);
        favoritepaths.clear();
        if (parts.size() > 3 && !parts.at(3).isEmpty()) {
            QString rawFavs = parts.at(3);
            favoritepaths = rawFavs.split(";;", Qt::SkipEmptyParts);
            for(QString &path : favoritepaths) {
                path.replace("[COLON2]", "::");
            }
        }
        return true;
    }
    return false;
}
bool accountwidget::finduser(const QString &usernametofind, QString &foundpassword, QString &foundbestfriendname, QStringList &foundfavoritepaths) {
    QFile accountFile(accountfilepath);
    if (!accountFile.exists() || !accountFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream in(&accountFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QString currentusername;
        QString currentpass, currentbff;
        QStringList currentfavs;
        if (accountline(line, currentusername, currentpass, currentbff, currentfavs)) {
            if (currentusername == usernametofind) {
                foundpassword = currentpass;
                foundbestfriendname = currentbff;
                foundfavoritepaths = currentfavs;
                accountFile.close();
                return true;
            }
        }
    }
    accountFile.close();
    return false;
}
