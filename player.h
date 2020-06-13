#ifndef PLAYER_H
#define PLAYER_H

#include <QVBoxLayout>
#include <QLabel>

class Player
{
public:
    Player();
    QString getName();
    void setName(QString name);
    QString getPoints();
    void setPoints(QString points);
    QVBoxLayout *getLayout();

private:
    QLabel *nameLabel;
    QLabel *pointsLabel;
    QVBoxLayout *layout;
};

#endif // PLAYER_H
