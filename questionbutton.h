#ifndef QUESTIONBUTTON_H
#define QUESTIONBUTTON_H

#include <QPushButton>

class QuestionButton : public QPushButton
{
    Q_OBJECT
public:
    explicit QuestionButton(QPushButton *parent = nullptr);
    void setDifficulty(int difficulty);
    void setHeadingId(int headingId);
private:
    int difficulty;
    int headingId;
signals:

};

#endif // QUESTIONBUTTON_H
