#include "fibonaccilevels.h"
#include "dot.h"
#include "templates.h"

#include <QApplication>

#include <QPen>
#include <QDebug>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QAction>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>


//Всё очень нее карсиво. Нужно переделать.


FibonacciLevels::FibonacciLevels(Dot *startPos, Dot *endPos, QGraphicsItem *parent) : QGraphicsLineItem(parent), mStartPosDot(startPos), mEndPosDot(endPos)
{
	setFlag(ItemIsSelectable, true);
	setFlag(ItemIsMovable, true);
	setFlag(ItemSendsGeometryChanges, true);

	mMainLine = new QLineF(mStartPosDot -> pos(), mEndPosDot -> pos());
	//mMainLine.setP1(mStartPosDot -> pos());
	//mMainLine.setP2(mEndPosDot -> pos());

    mStartPosDot->setFibonacciLevelsMainLine(this);
    mEndPosDot->setFibonacciLevelsMainLine(this);
	this -> setZValue(-1);

	mLevelOneLine = new QLineF;
	mLevelOneLine->setPoints(mMainLine->p1(), QPointF(mMainLine->p2().x(), mMainLine->p1().y()));

	mLevelZeroLine = new QLineF;
	mLevelZeroLine->setPoints(mMainLine->p2(), QPointF(mMainLine->p1().x(), mMainLine->p2().y()));

	mLevel0236Line = new QLineF;
	mLevel0236Line->setPoints(QPointF(mMainLine->p1().x(), mMainLine->pointAt(0.236).y()), QPointF(mMainLine->p2().x(), mMainLine->pointAt(0.236).y()));

	mLevel0382Line = new QLineF;
	mLevel0382Line->setPoints(QPointF(mMainLine->p1().x(), mMainLine->pointAt(0.382).y()), QPointF(mMainLine->p2().x(), mMainLine->pointAt(0.382).y()));

	mLevel05Line = new QLineF;
	mLevel05Line->setPoints(QPointF(mMainLine->p1().x(), mMainLine->pointAt(0.5).y()), QPointF(mMainLine->p2().x(), mMainLine->pointAt(0.5).y()));

	mLevel0618Line = new QLineF;
	mLevel0618Line->setPoints(QPointF(mMainLine->p1().x(), mMainLine->pointAt(0.618).y()), QPointF(mMainLine->p2().x(), mMainLine->pointAt(0.618).y()));

	mLevel0786Line = new QLineF;
	mLevel0786Line->setPoints(QPointF(mMainLine->p1().x(), mMainLine->pointAt(0.786).y()), QPointF(mMainLine->p2().x(), mMainLine->pointAt(0.786).y()));

	mLevel1272Line = new QLineF;

	mLevel1618Line = new QLineF;

	mLevel2618Line = new QLineF;

	mLevel4263Line = new QLineF;

	// mLinePointersMap.insert(1.0, mLevelOneLine);
	// mLinePointersMap.insert(0.0, mLevelZeroLine);
	// mLinePointersMap.insert(0.236, mLevel0236Line);
	// mLinePointersMap.insert(0.382, mLevel0382Line);
	// mLinePointersMap.insert(0.5, mLevel05Line);
	// mLinePointersMap.insert(0.618, mLevel0618Line);
	// mLinePointersMap.insert(0.786, mLevel0786Line);
	// mLinePointersMap.insert(1.272, mLevel1272Line);
	// mLinePointersMap.insert(1.618, mLevel1618Line);
	// mLinePointersMap.insert(2.618, mLevel2618Line);
	// mLinePointersMap.insert(4.618, mLevel4263Line);

	createActions();
	createMenus();

	setLine(*mMainLine);
}

FibonacciLevels::~FibonacciLevels()
{
	delete mMainLine;
	delete mLevelOneLine;
	delete mLevelZeroLine;
	delete mLevel0236Line;
	delete mLevel0382Line;
	delete mLevel05Line;
	delete mLevel0618Line;
	delete mLevel0786Line;
	delete mLevel1272Line;
	delete mLevel1618Line;
	delete mLevel2618Line;
	delete mLevel4263Line;


	delete setupAction;


	delete showZeroLevelAction;
	delete show0236LevelAction;
	delete show0382LevelAction;
	delete show05LevelAction;
	delete show0618LevelAction;
	delete show786LevelAction;
	delete showOneLevelAction;

	delete deleteFiboLevelsAction;
	delete fiboLevelsContextMenu;
}

void FibonacciLevels::updatePosition()
{
	mMainLine -> setPoints(mapFromItem(mStartPosDot, 0, 0), mapFromItem(mEndPosDot, 0, 0));
	//mMainLine -> setPoints(mStartPosDot -> getCenter(), mEndPosDot -> getCenter());
	mLevelOneLine->setPoints(mMainLine -> p1(), QPointF(mMainLine -> p2().x(), mMainLine -> p1().y()));
	mLevelZeroLine->setPoints(mMainLine -> p2(), QPointF(mMainLine -> p1().x(), mMainLine -> p2().y()));
	mLevel0236Line->setPoints(QPointF(mMainLine -> p1().x(), mMainLine -> pointAt(0.236).y()), QPointF(mMainLine -> p2().x(), mMainLine -> pointAt(0.236).y()));
	mLevel0382Line->setPoints(QPointF(mMainLine -> p1().x(), mMainLine -> pointAt(0.382).y()), QPointF(mMainLine -> p2().x(), mMainLine -> pointAt(0.382).y()));
	mLevel05Line->setPoints(QPointF(mMainLine -> p1().x(), mMainLine -> pointAt(0.5).y()), QPointF(mMainLine -> p2().x(), mMainLine -> pointAt(0.5).y()));
	mLevel0618Line->setPoints(QPointF(mMainLine -> p1().x(), mMainLine -> pointAt(0.618).y()), QPointF(mMainLine -> p2().x(), mMainLine -> pointAt(0.618).y()));
	mLevel0786Line->setPoints(QPointF(mMainLine -> p1().x(), mMainLine -> pointAt(0.786).y()), QPointF(mMainLine -> p2().x(), mMainLine -> pointAt(0.786).y()));

	setLine(*mMainLine);
}

QPainterPath FibonacciLevels::shape() const
{
	QPainterPath path;
	path.addRect(QRectF(mMainLine->p1(), mMainLine->p2()).adjusted(-1, -1, +1, +1));

	return path;
}



// QVector<QLineF> &FibonacciLevels::getLineVector()
// {
//     return mLineVector;
// }
//Использую только if чтобы рисовала все нужные линии
//Если будет блок else if, то линии будут рисоваться не все
void FibonacciLevels::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen(Qt::black);
	painter -> setPen(pen);

	if(option->state & QStyle::State_Selected)
	{
		prepareGeometryChange();
		//pen.setStyle(Qt::DotLine);
		pen.setColor(Qt::green);
		painter -> setPen(pen);
		painter -> setBrush(Qt::NoBrush);
		pen.setWidth(4);
		update();
	}

	painter -> drawLine(*mMainLine);
	if(isLevelOneLine)
	{
		painter -> drawLine(*mLevelOneLine);
	}

	if(isLevelZeroLine)
	{
		painter -> drawLine(*mLevelZeroLine);
	}

	if(isLevel0236Line)
	{
		painter -> drawLine(*mLevel0236Line);
	}

	if(isLevel0382Line)
	{
		painter -> drawLine(*mLevel0382Line);
	}

	if(isLevel05Line)
	{
		painter -> drawLine(*mLevel05Line);
	}

	if(isLevel0618Line)
	{
		painter -> drawLine(*mLevel0618Line);
	}

	if(isLevel0786Line)
	{
		painter -> drawLine(*mLevel0786Line);
	}

	if(isLevel1272Line)
	{
		painter -> drawLine(*mLevel1272Line);
	}

	if(isLevel1618Line)
	{
		painter -> drawLine(*mLevel1618Line);
	}

	if(isLevel2618Line)
	{
		painter -> drawLine(*mLevel2618Line);
	}

	if(isLevel4236Line)
	{
		painter -> drawLine(*mLevel4263Line);
	}

}

void FibonacciLevels::createActions()
{
	QFont font("Times", 12, QFont::Bold);
	setupAction = new QAction(QObject::tr("Настроить уровни Фибоначчи"), this);

	showZeroLevelAction = new QAction(QObject::tr("Уровень 0.0"), this);
	showZeroLevelAction -> setFont(font);
	show0236LevelAction = new QAction(QObject::tr("Уровень 0.236"), this);
	show0382LevelAction = new QAction(QObject::tr("Уровень 0.382"), this);
	show05LevelAction = new QAction(QObject::tr("Уровень 0.5"), this);
	show0618LevelAction = new QAction(QObject::tr("Уровень 0.618"), this);
	show786LevelAction = new QAction(QObject::tr("Уровень 0.786"), this);
	showOneLevelAction = new QAction(QObject::tr("Уровень 1.0"), this);
	showOneLevelAction -> setFont(font);

	deleteFiboLevelsAction = new QAction(QObject::tr("Удалить эти уровни Фибоначчи"), this);


	//Показываем или скрываем уровень 0.0
	connect(showZeroLevelAction, &QAction::triggered, this, [this]() mutable { showOrHideFiboLevels(Functions::setInvertedBool, isLevelZeroLine, showZeroLevelAction) ;});
	//Показываем или скрываем уровень 0.236
	connect(show0236LevelAction, &QAction::triggered, this, [this]() mutable { showOrHideFiboLevels(Functions::setInvertedBool, isLevel0236Line, show0236LevelAction) ;});
	//Показываем или скрываем уровень 0.382
	connect(show0382LevelAction, &QAction::triggered, this, [this]() mutable { showOrHideFiboLevels(Functions::setInvertedBool, isLevel0382Line, show0382LevelAction) ;});
	//Показываем или скрываем уровень 0.5
	connect(show05LevelAction, &QAction::triggered, this, [this]() mutable { showOrHideFiboLevels(Functions::setInvertedBool, isLevel05Line, show05LevelAction) ;});
	//Показываем или скрываем уровень 0.618
	connect(show0618LevelAction, &QAction::triggered, this, [this]() mutable { showOrHideFiboLevels(Functions::setInvertedBool, isLevel0618Line, show0618LevelAction) ;});
	//Показываем или скрываем уровень 0.786
	connect(show786LevelAction, &QAction::triggered, this, [this]() mutable { showOrHideFiboLevels(Functions::setInvertedBool, isLevel0786Line, show786LevelAction) ;});
	//Показываем или скрываем уровень 0.786
	connect(showOneLevelAction, &QAction::triggered, this, [this]() mutable { showOrHideFiboLevels(Functions::setInvertedBool, isLevelOneLine, showOneLevelAction) ;});
}

void FibonacciLevels::createMenus()
{
	fiboLevelsContextMenu = new QMenu;
	fiboLevelsContextMenu -> addAction(setupAction);
	fiboLevelsContextMenu -> addSection("Показать уровни");
	fiboLevelsContextMenu -> addAction(showZeroLevelAction);
	fiboLevelsContextMenu -> addAction(show0236LevelAction);
	fiboLevelsContextMenu -> addAction(show0382LevelAction);
	fiboLevelsContextMenu -> addAction(show05LevelAction);
	fiboLevelsContextMenu -> addAction(show0618LevelAction);
	fiboLevelsContextMenu -> addAction(show786LevelAction);
	fiboLevelsContextMenu -> addAction(showOneLevelAction);


	fiboLevelsContextMenu -> addSeparator();
	fiboLevelsContextMenu -> addAction(deleteFiboLevelsAction);
	//connect(fiboLevelsContextMenu, &QMenu::aboutToHide, this, [this](){ scene() -> clearSelection();});
	//connect(fiboLevelsContextMenu, &QMenu::aboutToHide, this, [this](){ selectAllItems();});
	connect(fiboLevelsContextMenu, &QMenu::aboutToHide, this, [this](){ unSelectAllItems();});
}
//Если флаг на видимость линии стоит в false
//инвентируем на true
//Выделяем показанную линию утолщённым шрифтом
//Потом нужно будет доделать иконки как checked и unchecked

//Первый аргумент - это указатель на функцию
//не знаю эффективно или нет, решил написать, чтобы вспомнить
void FibonacciLevels::showOrHideFiboLevels(void (*iverterFunction)(bool&), bool &levelFlag, QAction *action)
{
	QFont font("Times", 12, QFont::Bold);
	if(!levelFlag) {
		iverterFunction(levelFlag);
		action->setFont(font);
	} else {
		iverterFunction(levelFlag);
		font = qApp->font();
		action->setFont(font);
	}
}

void FibonacciLevels::selectAllItems()
{
	this->setSelected(true);
	mStartPosDot->setSelected(true);
	mEndPosDot->setSelected(true);
	//updatePosition();
}

void FibonacciLevels::unSelectAllItems()
{
	this->setSelected(false);
	mStartPosDot->setSelected(false);
	mEndPosDot->setSelected(false);
}
void FibonacciLevels::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	scene() -> clearSelection();
	//setSelected(true);
	selectAllItems();
	fiboLevelsContextMenu -> popup(event -> screenPos());
	//QGraphicsLineItem::contextMenuEvent(event);
}

void FibonacciLevels::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(event -> button() == Qt::LeftButton)
	{
		// this -> setSelected(true);
		// mStartPosDot -> setSelected(true);
		// mEndPosDot -> setSelected(true);
		//mStartPosDot -> setPos(mMainLine -> p1());
		//mEndPosDot -> setPos(mMainLine -> p2());
		//this -> updatePosition();
		mStartPosDot -> setPos(mStartPosDot -> pos());
		mEndPosDot -> setPos(mEndPosDot -> pos());
		updatePosition();
		selectAllItems();
		//updatePosition();
		QGraphicsLineItem::mousePressEvent(event);
	}
}

QVariant FibonacciLevels::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemPositionChange && scene())
	{
		selectAllItems();
		updatePosition();
	}
	return QGraphicsItem::itemChange(change, value);
}

void FibonacciLevels::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		// this -> setSelected(false);
		// mStartPosDot -> setSelected(false);
		// mEndPosDot -> setSelected(false);
		//
		//scene() -> clearSelection();
		//QGraphicsLineItem::mouseReleaseEvent(event);
		unSelectAllItems();
		updatePosition();
	}
	//scene() -> clearSelection();

	QGraphicsLineItem::mouseReleaseEvent(event);
}

void FibonacciLevels::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	//mStartPosDot -> setPos(mMainLine -> p1());
	//mEndPosDot -> setPos(mMainLine -> p2());
	//this -> updatePosition();
	// mStartPosDot -> setPos(mStartPosDot -> pos());
	// mEndPosDot -> setPos(mEndPosDot -> pos());
	selectAllItems();
	updatePosition();
	QGraphicsLineItem::mouseMoveEvent(event);
}
