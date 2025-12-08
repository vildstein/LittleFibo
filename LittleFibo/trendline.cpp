#include "trendline.h"
#include "dot.h"

#include <QMouseEvent>
#include <QPen>
#include <QDebug>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QAction>
#include "mainwindowscene.h"

//explicit TrendLine(const QPointF& startPos, const QPointF& endPos, QGraphicsItem *parent = nullptr);

TrendLine::TrendLine(Dot* startPos, Dot* endPos, MainWindowScene* scene, QGraphicsItem* parent) : QGraphicsLineItem(parent),//QGraphicsObject(parent),
    m_StartPosDot(startPos),
    m_EndPosDot(endPos),
    mScene(scene),
    mLine(new QLineF{})
{
	setFlag(ItemIsSelectable, true);
	setFlag(ItemIsMovable, true);
    //setFlag(ItemSendsGeometryChanges, true);

	createActions();
	createMenues();

    //mStartPosDot->setLine(this);
   // mEndPosDot->setLine(this);
    this->setZValue(0);

    m_StartPosDot->setParentItem(this);
    m_EndPosDot->setParentItem(this);


    mScene->addItem(m_StartPosDot);//mScene->addItem(mStartPosDot.get());
    mScene->addItem(m_EndPosDot);//mScene->addItem(mEndPosDot.get());
    updatePosition();
}

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

	mScene->addItem(m_StartPosDot);
	mScene->addItem(m_EndPosDot);
	mScene->addItem(this);

	setLine(*mLine);
	updatePosition();

	auto posPOne =  mLine->p1();
	auto posPTwo =  mLine->p2();

	qInfo() << posPOne << posPTwo;
	m_StartPosDot->setPos(posPOne);

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

void TrendLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen mPen;
	mPen.setWidth(2);
	mPen.setColor(Qt::red);

    painter->drawRect(boundingRect());

	if (option->state & QStyle::State_Selected) {
		prepareGeometryChange();

		//pen.setStyle(Qt::DotLine);
		mPen.setColor(Qt::green);
		painter->setPen(mPen);
		painter->setBrush(Qt::NoBrush);
		mPen.setWidth(4);
		painter->drawRect(boundingRect());
		update();
	}

	mPen.setColor(Qt::green);
	painter->setBrush(Qt::NoBrush);
	painter->setPen(mPen);
    painter->drawLine(*mLine);
}

void TrendLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	setSelected(true);
	m_StartPosDot->setSelected(true);
	m_EndPosDot->setSelected(true);

	update();

    QGraphicsLineItem::mousePressEvent(event);
}

QVariant TrendLine::itemChange(GraphicsItemChange change, const QVariant& value)
{
	if(change == QGraphicsItem::ItemPositionHasChanged) {
		auto posPOne =  mLine->p1();
		auto posPTwo =  mLine->p2();

		qInfo() << posPOne << posPTwo << m_StartPosDot->pos() << m_EndPosDot->pos() << value.toPointF();
		m_StartPosDot->setPos(posPOne);

		qInfo() << line().p1() << line().p2();



		//m_StartPosDot->updateStartPosition(this);
        //mEndPosDot  -> setPos(mLine.p2());

    }

    return QGraphicsLineItem::itemChange(change, value);
}

void TrendLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	setSelected(false);
	m_StartPosDot->setSelected(false);
	m_EndPosDot->setSelected(false);

	updatePosition();

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
