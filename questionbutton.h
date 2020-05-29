#ifndef QUESTIONBUTTON_H
#define QUESTIONBUTTON_H

#include <QPushButton>

class QuestionButton : public QPushButton
{
    Q_OBJECT
public:
    explicit QuestionButton(QPushButton *parent = nullptr);
    void setPrice(int price);
    void setHeadingId(int headingId);
    int getPrice();
    int getHeadingId();
private:
    int price;
    int headingId;
signals:

};

#endif // QUESTIONBUTTON_H
