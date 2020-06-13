#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H


#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>

#include <QDebug>

class NetworkManager : public QObject
{

    Q_OBJECT

public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    QTcpSocket *socket;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docErr;

public slots:

    void connectToHost(QString ip);
    void sockReady();
    void sockDisc();
    void onSendName(QString name);
    void onInitFinished();

signals:

    void initGui(QJsonDocument doc);
    void showMessage();
    void setNames(QStringList names);
};

#endif // NETWORKMANAGER_H
