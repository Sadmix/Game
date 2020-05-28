#include "questionbutton.h"

QuestionButton::QuestionButton(QPushButton *parent) : QPushButton(parent)
{

}

void QuestionButton::setDifficulty(int difficulty){

    this->difficulty = difficulty;

}

void QuestionButton::setHeadingId(int headingId){

    this->headingId = headingId;

}
