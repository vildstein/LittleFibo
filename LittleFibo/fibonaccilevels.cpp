#include "fibonaccilevels.h"
#include "dot.h"

#include <QPen>
#include <QDebug>
#include <QPainter>
#include <QStyleOptionGraphicsItem>


FibonacciLevels::FibonacciLevels(Dot *startPos, Dot *endPos, QGraphicsItem *parent) : QGraphicsLineItem(parent), mStartPosDot(startPos), mEndPosDot(endPos)
{
    setFlag(ItemIsSelectable, true);
    setFlag(ItemIsMovable, true);
    setFlag(ItemSendsGeometryChanges, true);

    mMainLine = new QLineF(mStartPosDot -> pos(), mEndPosDot -> pos());
    //mMainLine.setP1(mStartPosDot -> pos());
    //mMainLine.setP2(mEndPosDot -> pos());

    mStartPosDot -> setFibonacciLevelsMainLine(this);
    mEndPosDot -> setFibonacciLevelsMainLine(this);
    this -> setZValue(-1);

    mLevelLine = new QLineF(mStartPosDot -> pos().x(), mStartPosDot -> pos().y(), mMainLine -> dx(), mMainLine -> y1());

    setLine(*mMainLine);


}

FibonacciLevels::~FibonacciLevels()
{
    delete mMainLine;
    delete mLevelLine;

    qInfo() << "Destructor Of FiboLevels worked";
}

void FibonacciLevels::updatePosition()
{
    mMainLine -> setPoints(mapFromItem(mStartPosDot, 0, 0), mapFromItem(mEndPosDot, 0, 0));
    setLine(*mMainLine);
}

void FibonacciLevels::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black);
    painter -> setPen(pen);

    painter -> drawLine(*mMainLine);

    painter -> drawLine(*mLevelLine);

}
