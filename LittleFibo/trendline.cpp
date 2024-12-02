#include "trendline.h"
#include "dot.h"


#include <QPen>
#include <QDebug>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QAction>

//explicit TrendLine(const QPointF& startPos, const QPointF& endPos, QGraphicsItem *parent = nullptr);

TrendLine::TrendLine(const QPointF& startPos, const QPointF& endPos, QGraphicsItem *parent) : QGraphicsObject(parent),
	mStartPosDot(new Dot(startPos)),
	mEndPosDot(new Dot(endPos)),
	mLine(new Line((mStartPosDot->pos()), (mEndPosDot->pos())))
{
	setFlag(ItemIsSelectable, true);
	setFlag(ItemIsMovable, true);
	setFlag(ItemSendsGeometryChanges, true);

	createActions();
	createMenues();

	mStartPosDot->setLine(this);
	mEndPosDot->setLine(this);
	this->setZValue(-1);
	//setLine(*mLine);
}

TrendLine::~TrendLine() = default;

//void TrendLine::updatePosition()
//{
//	mLine->setPoints(mStartPosDot->pos(), mEndPosDot->pos());
//	//setLine(*mLine);
//}

QPointF TrendLine::getStartPos() const
{
	return mStartPosDot->pos();
}

QRectF TrendLine::boundingRect() const
{
	QRectF rect(-200, -200, +200, +200);
	return rect;
}

QPainterPath TrendLine::shape() const
{
	QPainterPath path;
	path.addEllipse(boundingRect());
	return path;
}

//QRectF TrendLine::boundingRect() const
//{
//	qreal extra = pen().width() + 20 /2.0;
//	return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(), line().p2().y() - line().p1().y())).normalized().adjusted(-extra, -extra, extra, extra);
//}

//QPainterPath TrendLine::shape() const
//{
//	QPainterPath path = QGraphicsLineItem::shape();
//	path.addRect(mLine->x1() - 1, mLine->y1() + 1, mLine->x2() + 1, mLine->y2() + 1);
//	return path;
//}

void TrendLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen mPen;
	mPen.setWidth(2);
	mPen.setColor(Qt::red);

	if (option->state & QStyle::State_Selected) {
		prepareGeometryChange();
		//pen.setStyle(Qt::DotLine);
		mPen.setColor(Qt::green);
		painter->setPen(mPen);
		painter->setBrush(Qt::NoBrush);
		mPen.setWidth(4);
		update();
	}

	painter->setPen(mPen);
	//painter->drawLine(*mLine);
}

void TrendLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	this -> setSelected(true);
	mStartPosDot -> setSelected(true);
	mEndPosDot -> setSelected(true);

	QGraphicsObject::mousePressEvent(event);
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
	this->setSelected(false);
	mStartPosDot->setSelected(false);
	mEndPosDot->setSelected(false);
	QGraphicsObject::mouseReleaseEvent(event);
}

void TrendLine::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}

void TrendLine::createActions()
{
	settingsAction = new QAction(tr(""), this);
	deleteAction = new QAction(tr(""), this);
}

void TrendLine::createMenues()
{

}

// Описание класса Line. Потом перенсу в другой файл
Line::Line(Dot* startDot, Dot* endDot, QGraphicsLineItem *parent) :
	QGraphicsLineItem(parent),
	mStartDot(startDot),
	mEndDot(endDot)
{
	setFlag(ItemIsSelectable, true);
	setFlag(ItemIsMovable, true);
	//QLineF mLine;
	mLine.setPoints(mStartDot->pos(), mEndDot->pos());
	setLine(mLine);
}

Line::Line(const QPointF &startPos, const QPointF &endPos, QGraphicsLineItem *parent) :
	mStartPos(startPos),
	mEndPos(endPos)
{

}

void Line::updatePosition()
{
	mLine.setPoints(mStartDot->pos(), mEndDot->pos());
	setLine(mLine);
}

QRectF Line::boundingRect() const
{

}

QPainterPath Line::shape() const
{

}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen mPen;
	mPen.setWidth(2);
	mPen.setColor(Qt::red);

	if (option->state & QStyle::State_Selected) {
		prepareGeometryChange();
		//pen.setStyle(Qt::DotLine);
		mPen.setColor(Qt::green);
		painter->setPen(mPen);
		painter->setBrush(Qt::NoBrush);
		mPen.setWidth(4);
		update();
	}

	painter->setPen(mPen);
	painter->drawLine(mLine);
}
