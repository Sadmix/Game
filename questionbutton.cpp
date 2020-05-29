#include "questionbutton.h"

QuestionButton::QuestionButton(QPushButton *parent) : QPushButton(parent)
{

}

void QuestionButton::setPrice(int price){

    this->price = price;

}

void QuestionButton::setHeadingId(int headingId){

    this->headingId = headingId;

}

int QuestionButton::getPrice()
{
    return price;
}

int QuestionButton::getHeadingId()
{
    return headingId;
}
