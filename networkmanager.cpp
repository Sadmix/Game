#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
        socket = new QTcpSocket;
        connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));
        socket->connectToHost("127.0.0.1", 5555);
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
                    // message about true connection
                    // initialization request
                } else {
                    // message about false connection
                }
            } else

            if (doc.object().value("type").toString() == "initialization"){
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
