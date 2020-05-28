#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    centralWidget = new QWidget;
    mainLayout = new QVBoxLayout;
    questionsLayout = new QGridLayout;
    playersLayout = new QHBoxLayout;
    answerBtn  = new QPushButton;

    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);
    mainLayout->addLayout(playersLayout, 0);
    mainLayout->addLayout(questionsLayout, 1);
    mainLayout->addWidget(answerBtn, 2);

    for(int i = 1; i < 6; i++){
        for(int j = 1; j < 6; j++){
            QuestionButton *btn = new QuestionButton();
            btn->setHeadingId(i);
            btn->setDifficulty(j);
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
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

