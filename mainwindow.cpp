#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&networkManager, SIGNAL(initGui(QJsonDocument)), this, SLOT(initGui(QJsonDocument)));
    connect(&networkManager, SIGNAL(showMessage()), &connectWindow, SLOT(showMessage()));
    connect(&networkManager, SIGNAL(setName(QString)), this, SLOT(onSetName(QString)));
    connect(&connectWindow, SIGNAL(closeApp()), this, SLOT(close()));
    connect(&connectWindow, SIGNAL(connectToHost(QString)), &networkManager, SLOT(connectToHost(QString)));
    connect(&connectWindow, SIGNAL(setName(QString)), this, SLOT(onSetName(QString)));
    connect(this, SIGNAL(sendName(QString)), &networkManager, SLOT(onSendName(QString)));

    centralWidget = new QWidget;
    mainLayout = new QVBoxLayout;
    questionsLayout = new QGridLayout;
    playersLayout = new QHBoxLayout;
    answerBtn  = new QPushButton;
    connectWindow.setWindowTitle("Connect to server");
    connectWindow.show();

    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);
    mainLayout->addLayout(playersLayout, 0);
    mainLayout->addLayout(questionsLayout, 1);
    mainLayout->addWidget(answerBtn, 2);

    for(int i = 1; i < 6; i++){
        for(int j = 1; j < 6; j++){
            QuestionButton *btn = new QuestionButton();
            btn->setHeadingId(i);
            btn->setPrice(j);
            btn->setMinimumSize(100, 100);
            questionsLayout->addWidget(btn, i, j+1);
            questionBtns.push_back(btn);
        }
    }

    for(int i = 1; i < 6; i++){
        QLabel *label = new QLabel;
        label->setAlignment(Qt::AlignCenter);
        label->setText("Heading №" + QString::number(i));
        questionsLayout->addWidget(label, i, 0);
        headings.push_back(label);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
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
    emit sendName(players[0].getName());
}

void MainWindow::showMessage(){
    QMessageBox::information(this, "Error", "Failed to connect");
}

void MainWindow::onSetName(QString name){
    Player thisPlayer;
    thisPlayer.setName(name);
    players.append(thisPlayer);
    playersLayout->addLayout(thisPlayer.getLayout());
}
