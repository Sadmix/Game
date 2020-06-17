#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    btnsActive = false;

    centralWidget = new QWidget;
    questionWidget = new QWidget;
    mainLayout = new QVBoxLayout;
    questionLayout = new QVBoxLayout;
    buttonsLayout = new QGridLayout;
    playersLayout = new QHBoxLayout;
    answerBtn  = new QPushButton;
    questText = new QLabel;

    connect(&networkManager, SIGNAL(initGui(QJsonDocument)), this, SLOT(initGui(QJsonDocument)));
    connect(&networkManager, SIGNAL(showMessage()), &connectWindow, SLOT(showMessage()));
    connect(&networkManager, SIGNAL(setNames(QStringList)), this, SLOT(onSetNames(QStringList)));
    connect(&connectWindow, SIGNAL(closeApp()), this, SLOT(close()));
    connect(this, SIGNAL(initFinished()), &networkManager, SLOT(onInitFinished()));
    connect(&connectWindow, SIGNAL(connectToHost(QString)), &networkManager, SLOT(connectToHost(QString)));
    connect(&connectWindow, SIGNAL(setName(QString)), this, SLOT(onSetName(QString)));
    connect(this, SIGNAL(sendName(QString)), &networkManager, SLOT(onSendName(QString)));
    connect(&networkManager, SIGNAL(choosePlayer(QString)), this, SLOT(onChoosePlayer(QString)));
    connect(this, SIGNAL(chooseQuestion(int, int)), &networkManager, SLOT(onChooseQuestion(int, int)));
    connect(&networkManager, SIGNAL(showText(QString)), this, SLOT(onShowText(QString)));
    connect(answerBtn, SIGNAL(clicked()), &networkManager, SLOT(sendAnswer()));
    connect(&networkManager, SIGNAL(blockButton(bool)), this, SLOT(onBlockButton(bool)));
    connect(&networkManager, SIGNAL(updatePoints(QString, QString, bool)), this, SLOT(onUpdatePoints(QString, QString, bool)));
    connect(&networkManager, SIGNAL(removeBtn(int, int)), this, SLOT(onRemoveBtn(int, int)));

    connectWindow.setWindowTitle("Connect to server");
    connectWindow.show();

    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);
    questionWidget->setLayout(questionLayout);

    mainLayout->addLayout(playersLayout, 0);
    mainLayout->addLayout(buttonsLayout, 1);

    questionLayout->addWidget(questText, 0);
    questionLayout->addWidget(answerBtn, 1);

    for(int i = 1; i < 6; i++){
        for(int j = 1; j < 6; j++){
            QuestionButton *btn = new QuestionButton();
            btn->setHeadingId(i);
            btn->setPrice(j);
            btn->setMinimumSize(100, 100);
            btn->setEnabled(btnsActive);
            buttonsLayout->addWidget(btn, i, j+1);
            questionBtns.push_back(btn);
        }
    }

    connectButtons();

    for(int i = 1; i < 6; i++){
        QLabel *label = new QLabel;
        label->setAlignment(Qt::AlignCenter);
        label->setText("Heading №" + QString::number(i));
        buttonsLayout->addWidget(label, i, 0);
        headings.push_back(label);
    }

    questText->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPixelSize(30);
    questText->setFont(font);

    answerBtn->setMinimumHeight(100);

}

MainWindow::~MainWindow()
{

}

void MainWindow::initGui(QJsonDocument doc)
{
    for (auto btn : questionBtns){
        btn->setText(QString::number(doc.object().value("price"+QString::number(btn->getPrice())).toInt()));
    }
    for (int i = 0; i < 5; i++){
        headings[i]->setText(doc.object().value("heading"+QString::number(i+1)).toString());
    }
    this->show();
    connectWindow.close();
    emit sendName(playerName);
}

void MainWindow::showMessage(){
    QMessageBox::information(this, "Error", "Failed to connect");
}

void MainWindow::onSetNames(QStringList names){
    int i = 0;
    while(i < players.size() && i < names.size()){
        players[i].setName(names[i]);
        i++;
    }
    if(players.size() < names.size()){
        while(i < names.size()){
            Player player;
            player.setName(names[i]);
            players.append(player);
            playersLayout->addLayout(player.getLayout());
            i++;
        }
    }
    if(names.size() == 3){
        emit initFinished();
    }
}

void MainWindow::onSetName(QString name){
    playerName = name;
}

void MainWindow::onChoosePlayer(QString name){
    if (name == playerName){
        for (auto btn : questionBtns){
            btn->setEnabled(true);
        }
    } else {
        for(auto btn : questionBtns){
            btn->setEnabled(false);
        }
    }
}

void MainWindow::onQuestionButtonClicked(){
    QuestionButton *btn = (QuestionButton*)sender();
    emit chooseQuestion(btn->getPrice(), btn->getHeadingId());

}

void MainWindow::connectButtons(){
    for (auto btn : questionBtns){
        connect(btn, SIGNAL(clicked()), this, SLOT(onQuestionButtonClicked()));
    }
}

void MainWindow::onShowText(QString questText){
    this->questText->setText(questText);
    centralWidget = takeCentralWidget();
    setCentralWidget(questionWidget);
}

void MainWindow::onBlockButton(bool check){
    answerBtn->setEnabled(!check);
}

void MainWindow::onUpdatePoints(QString name, QString points, bool next){
    for(auto p : players){
        if (p.getName() == name){
            p.setPoints(points);
        }
    }
    if (next){
        onNextQuestion(name);
    }
    answerBtn->setEnabled(true);
}

void MainWindow::onNextQuestion(QString name){
    questionWidget = takeCentralWidget();
    setCentralWidget(centralWidget);
    onChoosePlayer(name);
}

void MainWindow::onRemoveBtn(int price, int headingId){
    for(auto btn : questionBtns){
        if(btn->getPrice() == price && btn->getHeadingId() == headingId){
            delete btn;
        }
    }
}
