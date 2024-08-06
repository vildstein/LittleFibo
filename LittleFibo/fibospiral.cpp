#include "fibospiral.h"
#include "dot.h"


#include <QPen>
#include <QDebug>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

FiboSpiral::FiboSpiral(Dot *startPos, Dot *endPos, QGraphicsItem *parent) : mStartPosDot(startPos), mEndPosDot(endPos), QGraphicsPathItem(parent)
{
    QGraphicsPathItem::setFlag(ItemIsSelectable, true);
    QGraphicsPathItem::setFlag(ItemIsMovable, true);

    mPath = new QPainterPath(mapFromItem(mStartPosDot, 0, 0));
    mPath -> lineTo(mEndPosDot -> pos());
    mStartPosDot -> setSpiral(this);
    mEndPosDot -> setSpiral(this);

    this -> setZValue(-1);

    setPath(*mPath);

    updatePosition();

    //QGraphicsLineItem::setLine(mLine);
}

FiboSpiral::~FiboSpiral()
{
    delete mPath;
    qInfo() << "Destructor Of FiboSpiral worked";
}

void FiboSpiral::updatePosition()
{
    //mLine.setPoints(mapFromItem(mStartPosDot, 0, 0), mapFromItem(mEndPosDot, 0, 0));
    //setLine(mLine);
    mPath-> clear();
    mPath -> moveTo(mapFromItem(mStartPosDot, 0, 0));
    mPath -> lineTo(mapFromItem(mEndPosDot, 0, 0));
    setPath(*mPath);
}

QRectF FiboSpiral::boundingRect() const
{
    const int margin = 10;

    return QRectF(mapFromItem(mStartPosDot, 0, 0), mapFromItem(mEndPosDot, 0, 0)).adjusted(-margin, -margin, +margin, +margin);
    //return QRectF(mStartPosDot -> pos(), QSizeF(mEndPosDot -> pos().x() - mStartPosDot -> pos().x(), mEndPosDot -> pos().y() - mStartPosDot -> pos().y())).normalized().adjusted(-margin, -margin, +margin, +margin);
    //return QRectF(mStartPosDot -> pos(), QSizeF(mEndPosDot -> pos().x() - mStartPosDot -> pos().x(), mEndPosDot -> pos().y() - mStartPosDot -> pos().y())).normalized().adjusted(-margin, -margin, +margin, +margin);

    //qreal extra = pen().width() + 20 /2.0;
    //return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(), line().p2().y() - line().p1().y())).normalized().adjusted(-extra, -extra, extra, extra);
}

QPainterPath FiboSpiral::shape() const
{
    QPainterPath path;
    //path.addEllipse(boundingRect());

    path.addRect(mStartPosDot -> pos().x() - 1, mStartPosDot -> pos().y() + 1, mEndPosDot -> pos().x() + 1, mEndPosDot -> pos().y() + 1);
    return path;
}

void FiboSpiral::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::green);
    painter -> setPen(pen);
    if(option -> state & QStyle::State_Selected)
    {
        pen.setColor(Qt::green);
        painter -> setPen(pen);
        //painter -> setBrush(Qt::green);
        //painter -> drawRect(boundingRect());
        painter -> drawRect(boundingRect());
    }
    painter -> drawPath(*mPath);

    painter -> setPen(Qt::black);
    painter -> drawText(mapFromItem(mStartPosDot, 5, 5), "1");
    painter -> drawText(mapFromItem(mEndPosDot, -5, -5), "2");

}

void FiboSpiral::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this -> setSelected(true);
    mStartPosDot -> setSelected(true);
    mEndPosDot -> setSelected(true);
    QGraphicsPathItem::mousePressEvent(event);
}

void FiboSpiral::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this -> setSelected(false);
    mStartPosDot -> setSelected(false);
    mEndPosDot -> setSelected(false);
    QGraphicsPathItem::mouseReleaseEvent(event);
}
