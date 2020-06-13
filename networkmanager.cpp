#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{

}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::sockReady(){

    if(socket->waitForConnected(500)){

        socket->waitForReadyRead(500);
        Data = socket->readAll();

        doc = QJsonDocument::fromJson(Data, &docErr);

        if(docErr.errorString().toInt() == QJsonParseError::NoError){

            if (doc.object().value("type").toString() == "connection" ){
                    qDebug() << "\nConnected";
                    Data = "{\"type\": \"initialization\"}";
                    socket->write(Data);
            } else

            if (doc.object().value("type").toString() == "initialization"){
                emit initGui(doc);
            } else

            if(doc.object().value("type").toString() == "upateName"){
                emit setName(doc.object().value("name").toString());
            }

            // some instructions

        } else {
            // message about parse error
        }
    }
}

void NetworkManager::connectToHost(QString ip){
    socket = new QTcpSocket;
    connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));
    socket->connectToHost(ip, 5555);
}

void NetworkManager::sockDisc(){
    socket->deleteLater();
}

void NetworkManager::onSendName(QString name){

    Data = "{\"type\":\"regName\", \"name\":\"" + name.toUtf8() + "\"}";
    socket->write(Data);

}
