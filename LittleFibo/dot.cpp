#include "dot.h"
#include "trendline.h"
#include "fibospiral.h"
#include "fibonaccilevels.h"

#include <QPainter>
#include <QPen>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

//Удалить потом
#include <QDebug>

Dot::Dot(QGraphicsEllipseItem* parent) : QGraphicsEllipseItem(parent)
{
	setFlag(ItemIsSelectable, true);
	setFlag(ItemIsMovable, true);
	setFlag(ItemSendsGeometryChanges, true);

	mItemRect = QRectF{mCenter - QPointF(3.0, 3.0), mCenter + QPointF(3.0, 3.0)};
}

Dot::Dot(const QPointF &pos, QGraphicsEllipseItem* parent) : QGraphicsEllipseItem(parent)
{
	setPos(pos);
	setFlag(ItemIsSelectable, true);
	setFlag(ItemIsMovable, true);
	setFlag(ItemSendsGeometryChanges, true);

	mItemRect = QRectF{mCenter - QPointF(3.0, 3.0), mCenter + QPointF(3.0, 3.0)};

}

void Dot::updateStartPosition(TrendLine* trendLine)
{
    this->setPos(trendLine->getStartPos());
}

void Dot::updateEndPosition(TrendLine* trendLine)
{
	//this -> setPos(trendLine -> getEndPos());
}

QPointF Dot::getCenter() const
{
	return mCenter;
}

void Dot::setLine(TrendLine* trendLine)
{
	mTrendLine = trendLine;
}

void Dot::setSpiral(FiboSpiral* spiral)
{
	mSpiral = spiral;
}

void Dot::setFibonacciLevelsMainLine(FibonacciLevels* mainLine)
{
	mFibonacciLevelsMainLine = mainLine;
}

QRectF Dot::boundingRect() const
{
	const int margin = 1;
	return mItemRect.adjusted(-margin, -margin, +margin, +margin);
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
		//painter -> drawRect(boundingRect());
		painter -> drawEllipse(boundingRect());
	}
	painter -> setPen(pen);
	//painter -> drawRect(boundingRect());
	painter -> drawEllipse(boundingRect());
}

QVariant Dot::itemChange(GraphicsItemChange change, const QVariant &value)
{
	//Write for switch

	if(change == QGraphicsItem::ItemPositionHasChanged) {
		if (mTrendLine != nullptr) {
            mTrendLine->updatePosition();
		}
		else if(mSpiral != nullptr) {
            mSpiral->updatePosition();
		}
		else if(mFibonacciLevelsMainLine != nullptr) {
            mFibonacciLevelsMainLine->updatePosition();
		}
	}
	return QGraphicsItem::itemChange(change, value);
}
/*
void Dot::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	setSelected(true);
	QGraphicsEllipseItem::mousePressEvent(event);
}
*/
/*
void Dot::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	setSelected(false);
	QGraphicsEllipseItem::mousePressEvent(event);
}
*/
