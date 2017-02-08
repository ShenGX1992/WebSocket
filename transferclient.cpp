#include "transferclient.h"
#include "ui_transferclient.h"

TransferClient::TransferClient(const QUrl &url, QWidget *parent) :
    QDialog(parent),
    m_url(url),
    ui(new Ui::TransferClient)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    move((QApplication::desktop()->width() - width()) / 2,
         (QApplication::desktop()->height() - height()) / 2);
}

TransferClient::~TransferClient()
{
    delete ui;
}

void TransferClient::onConnected()
{
        ui->listWidget->addItem("WebSocket connected");
        qDebug() << "WebSocket connected";
    QObject::connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &TransferClient::onTextMessageReceived);
}

void TransferClient::unConnected()
{
        ui->listWidget->addItem( "WebSocket connected failed");
        qDebug() << "WebSocket connected failed";
}

void TransferClient::closed()
{
    ui->listWidget->addItem( "WebSocket closed");
    qDebug() << "WebSocket closed";
    m_webSocket.close();
}

void TransferClient::onTextMessageReceived(QString message)
{
    QString RECstring = "Receive:";
    RECstring.append(message);
    ui->listWidget->addItem(RECstring);
        qDebug() << "Message received:" << message;
}
void TransferClient::on_pushButton_connect_clicked()
{
    QString URLstring = "WebSocket server:";
    URLstring.append(m_url.toString());
    ui->listWidget->addItem(URLstring);
    qDebug() << "WebSocket server:" << m_url;
    /*QObject::*/connect(&m_webSocket, &QWebSocket::connected, this, &TransferClient::onConnected);
    /*QObject::*/connect(&m_webSocket, &QWebSocket::disconnected, this, &TransferClient::unConnected);
    m_webSocket.open(QUrl(m_url));
}

void TransferClient::on_pushButton_disconnect_clicked()
{
    ui->listWidget->addItem( "WebSocket closed");
    qDebug() << "WebSocket closed";
    m_webSocket.close();
}

void TransferClient::on_pushButton_send_clicked()
{
    ui->listWidget->addItem("Text Send");
    m_webSocket.sendTextMessage(ui->lineEdit_input->text());
}

void TransferClient::on_pushButton_Quit_clicked()
{
    m_webSocket.close();
    close();
}
