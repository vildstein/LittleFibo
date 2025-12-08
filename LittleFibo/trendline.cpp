#include "trendline.h"
#include "dot.h"

#include <QMouseEvent>
#include <QPen>
#include <QDebug>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QAction>
#include "mainwindowscene.h"

TrendLine::TrendLine(MainWindowScene* scene, QGraphicsItem* parent) : QGraphicsLineItem(parent), mScene(scene), mLine(new QLineF)
{
	setFlag(ItemIsSelectable, true);
	setFlag(ItemIsMovable, true);
	setFlag(ItemSendsGeometryChanges, true);

	createActions();
	createMenues();
	setZValue(0);

	m_StartPosDot = new Dot(QPointF(200, 200));
	m_EndPosDot = new Dot(QPointF(400, 400));
	mLine->setPoints(m_StartPosDot->pos(), m_EndPosDot->pos());

	m_StartPosDot->setLine(this);
	m_EndPosDot->setLine(this);

	m_StartPosDot->setZValue(1.0);
	m_EndPosDot->setZValue(1.0);

	m_StartPosDot->setParentItem(this);
	m_EndPosDot->setParentItem(this);

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
	mLine->setPoints(m_StartPosDot->pos(), m_EndPosDot->pos());
    setLine(*mLine);
}

void TrendLine::updatePosition(const QPointF& pos)
{
	//mLine->
}

QPointF TrendLine::getStartPos() const
{
    return m_StartPosDot->pos();
}

QRectF TrendLine::boundingRect() const
{
	QRectF rect(m_StartPosDot->pos(), m_EndPosDot->pos());
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
		painter->setPen(mPen);
		painter->setBrush(Qt::NoBrush);
		mPen.setWidth(6);
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
	m_StartPosDot->setSelected(true);
	m_EndPosDot->setSelected(true);

	update();

    QGraphicsLineItem::mousePressEvent(event);
}
/*
QVariant TrendLine::itemChange(GraphicsItemChange change, const QVariant& value)
{
	if(change == QGraphicsItem::ItemPositionHasChanged) {
		//auto posPOne =  mLine->p1();
		//auto posPTwo =  mLine->p2();

		//auto rect = m_StartPosDot->rect();
		//rect.moveTo(posPOne);
		//m_StartPosDot->setPos(QPointF(0, 0));

		//auto ch = value.toPointF();
		//m_StartPosDot->moveBy(ch.rx(), ch.ry());








		//m_StartPosDot->updateStartPosition(this);
        //mEndPosDot  -> setPos(mLine.p2());

    }

    return QGraphicsLineItem::itemChange(change, value);
}
*/
void TrendLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	setSelected(false);
	m_StartPosDot->setSelected(false);
	m_EndPosDot->setSelected(false);

	update();

    QGraphicsLineItem::mouseReleaseEvent(event);
}

// void TrendLine::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
// {

// }

void TrendLine::createActions()
{
    //settingsAction = new QAction(tr(""), this);
    //deleteAction = new QAction(tr(""), this);
}

void TrendLine::createMenues()
{

}
