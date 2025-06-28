#include <QApplication>
#include "musicprocessor.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    musicplayer *window = musicplayer::getinstance();
    window->setWindowTitle("music player");
    window->resize(400, 300);
    window->show();
    return app.exec();
}
