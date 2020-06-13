#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class ConnectWindow;
}

class ConnectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectWindow(QWidget *parent = nullptr);
    ~ConnectWindow();

public slots:
    void showMessage();

private slots:
    void on_cancelBtn_clicked();

    void on_pushButton_2_clicked();

    void on_ipEdit_textEdited(const QString &arg1);

    void on_nameEdit_textChanged(const QString &arg1);

private:
    Ui::ConnectWindow *ui;
    QString ip;
    QString name;
signals:
    void closeApp();
    void connectToHost(QString ip);
    void setName(QString name);
};

#endif // CONNECTWINDOW_H
