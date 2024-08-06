#include "trendline.h"
#include "dot.h"


#include <QPen>
#include <QDebug>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

TrendLine::TrendLine(Dot *startPos, Dot *endPos, QGraphicsItem *parent) : QGraphicsLineItem(parent), mStartPosDot(startPos), mEndPosDot(endPos)
{
    setFlag(ItemIsSelectable, true);
    setFlag(ItemIsMovable, true);
    setFlag(ItemSendsGeometryChanges, true);
    mLine.setP1(mStartPosDot -> pos());
    mLine.setP2(mEndPosDot -> pos());

    mStartPosDot -> setLine(this);
    mEndPosDot -> setLine(this);
    this -> setZValue(-1);

    setLine(mLine);
}

void TrendLine::updatePosition()
{    
    mLine.setPoints(mapFromItem(mStartPosDot, 0, 0), mapFromItem(mEndPosDot, 0, 0));
    setLine(mLine);
}

QPointF TrendLine::getStartPos() const
{
    return mLine.p1();
}

QRectF TrendLine::boundingRect() const
{
    qreal extra = pen().width() + 20 /2.0;
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(), line().p2().y() - line().p1().y())).normalized().adjusted(-extra, -extra, extra, extra);
}

QPainterPath TrendLine::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addRect(mLine.x1() - 1, mLine.y1() + 1, mLine.x2() + 1, mLine.y2() + 1);
    return path;
}

void TrendLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen mPen = pen();
    mPen.setWidth(2);
    mPen.setColor(Qt::red);

    if(option->state & QStyle::State_Selected)
    {
        prepareGeometryChange();
        //pen.setStyle(Qt::DotLine);
        mPen.setColor(Qt::green);
        painter -> setPen(mPen);
        painter -> setBrush(Qt::NoBrush);
        mPen.setWidth(4);
        update();
    }

    painter -> setPen(mPen);
    painter -> drawLine(mLine);
}

void TrendLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this -> setSelected(true);
    mStartPosDot -> setSelected(true);
    mEndPosDot -> setSelected(true);

    QGraphicsLineItem::mousePressEvent(event);
}

// QVariant TrendLine::itemChange(GraphicsItemChange change, const QVariant &value)
// {
//     if(change == QGraphicsItem::ItemPositionChange)
//     {
//         mStartPosDot -> updateStartPosition(this);
//         //mEndPosDot  -> setPos(mLine.p2());

//     }

//     return QGraphicsItem::itemChange(change, value);
// }

void TrendLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this -> setSelected(false);
    mStartPosDot -> setSelected(false);
    mEndPosDot -> setSelected(false);
    QGraphicsLineItem::mouseReleaseEvent(event);
}

void TrendLine::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}
