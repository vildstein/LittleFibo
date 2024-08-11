#include "fibonaccilevels.h"
#include "dot.h"
#include "templates.h"

#include <QPen>
#include <QDebug>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QAction>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>


FibonacciLevels::FibonacciLevels(Dot *startPos, Dot *endPos, QGraphicsItem *parent) : QGraphicsLineItem(parent), mStartPosDot(startPos), mEndPosDot(endPos)
{
    setFlag(ItemIsSelectable, true);
    setFlag(ItemIsMovable, true);
    setFlag(ItemSendsGeometryChanges, true);

    mMainLine = new QLineF(mStartPosDot -> pos(), mEndPosDot -> pos());
    //mMainLine.setP1(mStartPosDot -> pos());
    //mMainLine.setP2(mEndPosDot -> pos());

    mStartPosDot -> setFibonacciLevelsMainLine(this);
    mEndPosDot -> setFibonacciLevelsMainLine(this);
    this -> setZValue(-1);

    mLevelOneLine = new QLineF;
    mLevelOneLine -> setPoints(mMainLine -> p1(), QPointF(mMainLine -> p2().x(), mMainLine -> p1().y()));

    mLevelZeroLine = new QLineF;
    mLevelZeroLine -> setPoints(mMainLine -> p2(), QPointF(mMainLine -> p1().x(), mMainLine -> p2().y()));

    mLevel0236Line = new QLineF;
    mLevel0236Line -> setPoints(QPointF(mMainLine -> p1().x(), mMainLine -> pointAt(0.236).y()), QPointF(mMainLine -> p2().x(), mMainLine -> pointAt(0.236).y()));

    mLevel0382Line = new QLineF;
    mLevel0382Line -> setPoints(QPointF(mMainLine -> p1().x(), mMainLine -> pointAt(0.382).y()), QPointF(mMainLine -> p2().x(), mMainLine -> pointAt(0.382).y()));

    mLevel05Line = new QLineF;
    mLevel05Line -> setPoints(QPointF(mMainLine -> p1().x(), mMainLine -> pointAt(0.5).y()), QPointF(mMainLine -> p2().x(), mMainLine -> pointAt(0.5).y()));

    mLevel0618Line = new QLineF;
    mLevel0618Line -> setPoints(QPointF(mMainLine -> p1().x(), mMainLine -> pointAt(0.618).y()), QPointF(mMainLine -> p2().x(), mMainLine -> pointAt(0.618).y()));

    mLevel0786Line = new QLineF;
    mLevel0786Line -> setPoints(QPointF(mMainLine -> p1().x(), mMainLine -> pointAt(0.786).y()), QPointF(mMainLine -> p2().x(), mMainLine -> pointAt(0.786).y()));

    mLevel1272Line = new QLineF;

    mLevel1618Line = new QLineF;

    mLevel2618Line = new QLineF;

    mLevel4263Line = new QLineF;

    mLinePointersMap.insert(1.0, mLevelOneLine);
    mLinePointersMap.insert(0.0, mLevelZeroLine);
    mLinePointersMap.insert(0.236, mLevel0236Line);
    mLinePointersMap.insert(0.382, mLevel0382Line);
    mLinePointersMap.insert(0.5, mLevel05Line);
    mLinePointersMap.insert(0.618, mLevel0618Line);
    mLinePointersMap.insert(0.786, mLevel0786Line);
    mLinePointersMap.insert(1.272, mLevel1272Line);
    mLinePointersMap.insert(1.618, mLevel1618Line);
    mLinePointersMap.insert(2.618, mLevel2618Line);
    mLinePointersMap.insert(4.618, mLevel4263Line);

    createActions();
    createMenus();

    setLine(*mMainLine);
}

FibonacciLevels::~FibonacciLevels()
{
    delete mMainLine;
    //Шаблонная функция. См. файл templates.h
    TemplatesFunctions::clearDynamicMap(mLinePointersMap);
    //TemplatesFunctions::clearDynamicVector(mQActionVector);

    if(!mQActionVector.isEmpty())
    {
        QVector<QAction*>::iterator i;
        for(i = mQActionVector.begin(); i!=mQActionVector.end(); ++i)
        {
            delete *i;
            *i=nullptr;
        }
        mQActionVector.clear();

    }
    qInfo() << "Destructor Of FiboLevels worked";
}

void FibonacciLevels::updatePosition()
{
    mMainLine -> setPoints(mapFromItem(mStartPosDot, 0, 0), mapFromItem(mEndPosDot, 0, 0));
    mLevelOneLine -> setPoints(mMainLine -> p1(), QPointF(mMainLine -> p2().x(), mMainLine -> p1().y()));
    mLevelZeroLine -> setPoints(mMainLine -> p2(), QPointF(mMainLine -> p1().x(), mMainLine -> p2().y()));
    mLevel0236Line -> setPoints(QPointF(mMainLine -> p1().x(), mMainLine -> pointAt(0.236).y()), QPointF(mMainLine -> p2().x(), mMainLine -> pointAt(0.236).y()));
    mLevel0382Line -> setPoints(QPointF(mMainLine -> p1().x(), mMainLine -> pointAt(0.382).y()), QPointF(mMainLine -> p2().x(), mMainLine -> pointAt(0.382).y()));
    mLevel05Line -> setPoints(QPointF(mMainLine -> p1().x(), mMainLine -> pointAt(0.5).y()), QPointF(mMainLine -> p2().x(), mMainLine -> pointAt(0.5).y()));
    mLevel0618Line -> setPoints(QPointF(mMainLine -> p1().x(), mMainLine -> pointAt(0.618).y()), QPointF(mMainLine -> p2().x(), mMainLine -> pointAt(0.618).y()));
    mLevel0786Line -> setPoints(QPointF(mMainLine -> p1().x(), mMainLine -> pointAt(0.786).y()), QPointF(mMainLine -> p2().x(), mMainLine -> pointAt(0.786).y()));

    setLine(*mMainLine);
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

void FibonacciLevels::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this -> setSelected(true);
    mStartPosDot -> setSelected(true);
    mEndPosDot -> setSelected(true);
    QGraphicsLineItem::mousePressEvent(event);
}
void FibonacciLevels::createActions()
{
    setupAction = new QAction(QObject::tr("Настроить уровни Фибоначчи"), this);

    showZeroLevelAction = new QAction(QObject::tr("Уровень 0.0"), this);
    show0236LevelAction = new QAction(QObject::tr("Уровень 0.236"), this);
    show0382LevelAction = new QAction(QObject::tr("Уровень 0.382"), this);
    show05LevelAction = new QAction(QObject::tr("Уровень 0.5"), this);
    show0618LevelAction = new QAction(QObject::tr("Уровень 0.618"), this);
    show786LevelAction = new QAction(QObject::tr("Уровень 0.786"), this);
    showOneLevelAction = new QAction(QObject::tr("Уровень 1.0"), this);

    deleteFiboLevelsAction = new QAction(QObject::tr("Удалить эти уровни Фибоначчи"), this);

    mQActionVector.append(std::move(setupAction));
    mQActionVector.append(std::move(showZeroLevelAction));
    mQActionVector.append(std::move(show0236LevelAction));
    mQActionVector.append(std::move(show0382LevelAction));
    mQActionVector.append(std::move(show05LevelAction));
    mQActionVector.append(std::move(show0618LevelAction));
    mQActionVector.append(std::move(show786LevelAction));
    mQActionVector.append(std::move(showOneLevelAction));

    mQActionVector.append(std::move(deleteFiboLevelsAction));
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

}
void FibonacciLevels::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene() -> clearSelection();
    setSelected(true);
    fiboLevelsContextMenu -> popup(event -> screenPos());

}
void FibonacciLevels::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this -> setSelected(false);
    mStartPosDot -> setSelected(false);
    mEndPosDot -> setSelected(false);
    QGraphicsLineItem::mouseReleaseEvent(event);
}
