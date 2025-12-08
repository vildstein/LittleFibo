#include "trendline.h"
#include "dot.h"

#include <QMouseEvent>
#include <QPen>
#include <QDebug>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QAction>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include "mainwindowscene.h"

TrendLine::TrendLine(MainWindowScene* scene, QGraphicsItem* parent) : QGraphicsLineItem(parent),
	mScene(scene),
	mLine(new QLineF)
{
	setFlag(ItemIsSelectable, true);
	setFlag(ItemIsMovable, true);
	setFlag(ItemSendsGeometryChanges, true);

	//createActions();

	setZValue(0);

	mStartPosDot = new Dot(QPointF(200, 200));
	mEndPosDot = new Dot(QPointF(400, 400));
	mLine->setPoints(mStartPosDot->pos(), mEndPosDot->pos());

	mStartPosDot->setLine(this);
	mEndPosDot->setLine(this);

	mStartPosDot->setZValue(1.0);
	mEndPosDot->setZValue(1.0);

	mStartPosDot->setParentItem(this);
	mEndPosDot->setParentItem(this);

	setLine(*mLine);
	updatePosition();
}

TrendLine::~TrendLine()
{
	//delete mLine;
	qInfo() << "Trend Line destroyed";
	//mScene->removeItem(mStartPosDot.get());
   // mScene->removeItem(mEndPosDot.get());
   // mScene->removeItem(this);
}

void TrendLine::updatePosition()
{
	mLine->setPoints(mStartPosDot->pos(), mEndPosDot->pos());
	setLine(*mLine);
}

QPointF TrendLine::getStartPos() const
{
	return mStartPosDot->pos();
}

void TrendLine::setMenuToOwn(QMenu* contextMenu)
{
	mContextMenu.reset(contextMenu); // first step
}

QRectF TrendLine::boundingRect() const
{
	QRectF rect(mStartPosDot->pos(), mEndPosDot->pos());
	return rect.normalized().adjusted(-8, -8, 8, 8);
}

QPainterPath TrendLine::shape() const
{
	QPainterPath path = QGraphicsLineItem::shape();
	return path;
}

void TrendLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen mPen;
	mPen.setColor(Qt::green);
	painter->setBrush(Qt::NoBrush);
	mPen.setWidth(1);//mPen.setWidth(4);
	painter->setPen(mPen);
	painter->drawPath(shape());//painter->drawLine(*mLine);

	if (option->state & QStyle::State_Selected) {
		prepareGeometryChange();

		mPen.setColor(Qt::red);
		painter->setBrush(Qt::NoBrush);
		mPen.setWidth(3);
		painter->setPen(mPen);
		//painter->drawRect(boundingRect());
		painter->drawLine(*mLine);
		//painter->drawPath(shape());
		update();
	}


	//painter->setPen(mPen);
	//painter->drawLine(*mLine);
	//painter->drawPath(shape());
}

void TrendLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	setSelected(true);
	mStartPosDot->setSelected(true);
	mEndPosDot->setSelected(true);

	update();

	QGraphicsLineItem::mousePressEvent(event);
}

void TrendLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	setSelected(false);
	mStartPosDot->setSelected(false);
	mEndPosDot->setSelected(false);

	update();

	QGraphicsLineItem::mouseReleaseEvent(event);
}

void TrendLine::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
	if (!mContextMenu.isNull()) {
		mScene->clearSelection();
		setSelected(true);
		mContextMenu->popup(event->screenPos());
	}
}

/*
void TrendLine::createActions()
{
	auto* settingsAction = new QAction(tr("Настройки линии тренда"));
	auto* deleteAction = new QAction(tr("Удалить эту линию тренда"));

	mContextMenu->addAction(settingsAction);
	mContextMenu->addAction(deleteAction);

}
*/
/*
void TrendLine::createMenues()
{

}
*/
