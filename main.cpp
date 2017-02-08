#include "transferclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TransferClient w(QUrl(QStringLiteral("ws://localhost:1234")));// "ws://192.168.0.117:1234"
    w.show();

    return a.exec();
}
