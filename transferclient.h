#ifndef TRANSFERCLIENT_H
#define TRANSFERCLIENT_H

#include <QDialog>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QKeyEvent>
#include <QThread>
#include <QTimer>
#include <cmath>
#include <QDebug>
#include <QMouseEvent>
#include <QDesktopWidget>

namespace Ui {
class TransferClient;
}

class TransferClient : public QDialog
{
    Q_OBJECT

public:
    explicit TransferClient(const QUrl &url,QWidget *parent = 0);
    ~TransferClient();

private Q_SLOTS:
    void onConnected();
    void unConnected();
    void closed();
    void onTextMessageReceived(QString message);

    void on_pushButton_connect_clicked();

    void on_pushButton_disconnect_clicked();

    void on_pushButton_send_clicked();

    void on_pushButton_Quit_clicked();

private:
    Ui::TransferClient *ui;
    QWebSocket m_webSocket;
    QUrl m_url;
};

#endif // TRANSFERCLIENT_H
