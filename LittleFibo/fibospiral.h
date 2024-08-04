#ifndef FIBOSPIRAL_H
#define FIBOSPIRAL_H

#include <QGraphicsPathItem>

class Dot;

class FiboSpiral : public QGraphicsPathItem
{
public:
    FiboSpiral(Dot *startPos, Dot *endPos, QGraphicsItem *parent = nullptr);


    //Геттеры


    //Сеттеры

protected:

private:
    Dot *mStartPosDot;
    Dot *mEndPosDot;

    QPainterPath mPath;

};

#endif // FIBOSPIRAL_H
