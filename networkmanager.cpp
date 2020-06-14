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
                    Data = "{\"type\": \"initialization\", \"operation\":\"start\"}";
                    socket->write(Data);
            } else

            if (doc.object().value("type").toString() == "initialization"){
                emit initGui(doc);
            } else

            if(doc.object().value("type").toString() == "updateNames"){
                QStringList names;
                QJsonArray arr = doc.object().value("names").toArray();
                for(auto obj : arr){
                    names.push_back(obj.toObject().value("name").toString());
                }
                emit setNames(names);
            }
            else if(doc.object().value("type").toString() == "game"){
                if (doc.object().value("operation").toString() == "start"){
                    QMessageBox::information(nullptr, "Game", "Game started");
                    QString name = doc.object().value("name").toString(); // {"type":"game", "operation":"choosePlayer", "name":"..."}
                    emit choosePlayer(name);
                }
            }
            else if(doc.object().value("type").toString() == "questionText"){
                emit showText(doc.object().value("value").toString());
            }

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

void NetworkManager::onInitFinished(){
     Data = "{\"type\":\"initialization\", \"operation\":\"finish\"}";
     socket->write(Data);
}

void NetworkManager::onChooseQuestion(int price, int headingId){
    Data = "{\"type\":\"chooseQuestion\", \"price\":\""+QString::number(price).toUtf8()+"\", \"headingId\":\"" + QString::number(headingId).toUtf8() + "\"}";
    socket->write(Data);
}

