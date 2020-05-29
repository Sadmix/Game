#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
        socket = new QTcpSocket;
        connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));
        socket->connectToHost("25.129.224.214", 5555);
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
                if((doc.object().value("status") == "true")){
                    qDebug() << "\nConnected";
                    Data = "{\"type\": \"initialization\"}";
                    socket->write(Data);
                } else {
                    qDebug() << "\nFailed to connect";
                }
            } else

            if (doc.object().value("type").toString() == "initialization"){
                emit initGui(doc);
                    // update name request
                    // {"type":"updateName", "name":"some_name"}
            } else

            if(doc.object().value("type").toString() == "name"){
                    // update names of players
            }

            // some instructions

        } else {
            // message about parse error
        }
    }

}


void NetworkManager::sockDisc(){
    socket->deleteLater();
}
