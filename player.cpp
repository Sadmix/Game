#include "player.h"

Player::Player()
{
    layout = new QVBoxLayout;
    nameLabel = new QLabel;
    pointsLabel = new QLabel;
    layout->addWidget(nameLabel, 0);
    layout->addWidget(pointsLabel, 1);
    nameLabel->setAlignment(Qt::AlignCenter);
    pointsLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setText("Player");
    pointsLabel->setText(QString::number(0));
}

QString Player::getName(){
    return nameLabel->text();
}
void Player::setName(QString name){
    nameLabel->setText(name);
}

QString Player::getPoints(){
    return pointsLabel->text();
}

void Player::setPoints(QString points){
    pointsLabel->setText(points);
}

QVBoxLayout* Player::getLayout(){
    return layout;
}
