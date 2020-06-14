#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

#include "player.h"
#include "networkmanager.h"
#include "questionbutton.h"
#include "connectwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *mainLayout;
    QVBoxLayout *questionLayout;
    QGridLayout *buttonsLayout;
    QHBoxLayout *playersLayout;
    QPushButton *answerBtn;
    QWidget *centralWidget;
    QWidget *questionWidget;
    QVector<QuestionButton*> questionBtns;
    NetworkManager networkManager;
    QVector<QLabel*> headings;
    QVector<Player> players;
    ConnectWindow connectWindow;
    QString playerName;
    QLabel *questText;

    bool btnsActive;

    void connectButtons();

public slots:
    void onChoosePlayer(QString name);
    void initGui(QJsonDocument doc);
    void showMessage();
    void onSetNames(QStringList names);
    void onSetName(QString name);
    void onQuestionButtonClicked();
    void onShowText(QString questText);

signals:

    void sendName(QString name);
    void initFinished();
    void chooseQuestion(int price, int headingId);
};
#endif // MAINWINDOW_H
