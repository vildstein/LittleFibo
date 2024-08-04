#include "trendline.h"
#include "dot.h"

TrendLine::TrendLine(Dot *startPos, Dot *endPos, QGraphicsItem *parent) : mStartPosDot(startPos), mEndPosDot(endPos), QGraphicsLineItem(parent)
{
    setFlag(ItemIsSelectable, true);
    setFlag(ItemIsMovable, true);
    mStartPosDot -> setLine(this);
    mEndPosDot -> setLine(this);
    this -> setZValue(-1);
    setLine(QLineF(mStartPosDot -> pos(), mEndPosDot -> pos()));
}

void TrendLine::updatePosition()
{
    setLine(QLineF(mStartPosDot -> pos(), mEndPosDot -> pos()));
}

void TrendLine::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}
