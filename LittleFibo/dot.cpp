#include "dot.h"
#include "trendline.h"

#include <QPainter>
#include <QPen>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

//Удалить потом
#include <QDebug>

Dot::Dot(QGraphicsItem *parent) : QGraphicsObject(parent)
{
    setFlag(ItemIsSelectable, true);
    setFlag(ItemIsMovable, true);
    setFlag(ItemSendsGeometryChanges, true);

    mItemRect = QRectF{mCenter - QPointF(3.0, 3.0), mCenter + QPointF(3.0, 3.0)};
}

void Dot::updateStartPosition(TrendLine *trendLine)
{
    this -> setPos(trendLine -> getStartPos());
}

void Dot::updateEndPosition(TrendLine *trendLine)
{

}

QPointF Dot::getCenter() const
{
    return mCenter;
}

void Dot::setLine(TrendLine *trendLine)
{
    mTrendLine = trendLine;
}

QRectF Dot::boundingRect() const
{
    return mItemRect;
}

QPainterPath Dot::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Dot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::red);
    painter -> setBrush(Qt::red);
    if(option -> state & QStyle::State_Selected)
    {
        pen.setColor(Qt::green);
        painter -> setPen(pen);
        painter -> setBrush(Qt::green);
        painter -> drawRect(boundingRect());
    }
    painter -> setPen(pen);
    painter -> drawRect(boundingRect());
}

QVariant Dot::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemPositionHasChanged)
    {
        mTrendLine -> updatePosition();
    }

    return QGraphicsItem::itemChange(change, value);
}

void Dot::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
}

void Dot::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setSelected(false);
    QGraphicsObject::mouseReleaseEvent(event);
}
