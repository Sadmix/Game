#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

#include "networkmanager.h"
#include "questionbutton.h"

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
    QGridLayout *questionsLayout;
    QHBoxLayout *playersLayout;
    QPushButton *answerBtn;
    QWidget *centralWidget;
    QVector<QuestionButton*> questionBtns;
    NetworkManager networkManager;

};
#endif // MAINWINDOW_H
