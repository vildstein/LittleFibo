#ifndef FIBONACCILEVELS_H
#define FIBONACCILEVELS_H

#include <QGraphicsLineItem>
class Dot;
class QAction;
class QMenu;

class FibonacciLevels : /*для Q_OBJECT и функции tr()*/ private QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    explicit FibonacciLevels(Dot *startPos = nullptr, Dot *endPos = nullptr, QGraphicsItem *parent = nullptr);
    virtual ~FibonacciLevels();

    void updatePosition();
    //Геттеры
    //QVector<QLineF> &getLineVector();

    //Сеттеры

protected:
    //virtual QRectF boundingRect() const override;
    //virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    //virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
    //Создать пункты меню
    void createActions();
    //Создать само Меню
    void createMenus();
    //Стартовые точки
    Dot *mStartPosDot;
    Dot *mEndPosDot;

    //Угловая линия, которая наискосок проходит через уровни 1.0 - 0.0
    QLineF *mMainLine = nullptr;
    //Линии - уровни
    QLineF *mLevelOneLine = nullptr;
    QLineF *mLevelZeroLine = nullptr;
    //Дополниетльные линии - уровни, которые строиятся от основной линии (косой)
    QLineF *mLevel0236Line = nullptr;
    QLineF *mLevel0382Line = nullptr;
    QLineF *mLevel05Line = nullptr;
    QLineF *mLevel0618Line = nullptr;
    QLineF *mLevel0786Line = nullptr;
    QLineF *mLevel1272Line = nullptr;
    QLineF *mLevel1618Line = nullptr;
    QLineF *mLevel2618Line = nullptr;
    QLineF *mLevel4263Line = nullptr;

    //Действия для меню
    QAction *setupAction;

    QAction *showZeroLevelAction;
    QAction *show0236LevelAction;
    QAction *show0382LevelAction;
    QAction *show05LevelAction;
    QAction *show0618LevelAction;
    QAction *show786LevelAction;
    QAction *showOneLevelAction;


    QAction *deleteFiboLevelsAction;

    //Меню
    QMenu *fiboLevelsContextMenu;



    QMap<double, QLineF*> mLinePointersMap;
    //Вектор для Пунктов меню, чтобы не прописывать
    //delete для каждого экшена
    QVector<QAction*> mQActionVector;



    //1.0
    bool isLevelOneLine{true};
    //0.0
    bool isLevelZeroLine{true};
    //0.236
    bool isLevel0236Line{false};
    //0.382
    bool isLevel0382Line{false};
    //0.5
    bool isLevel05Line{false};
    //0.618
    bool isLevel0618Line{false};
    //0.786
    bool isLevel0786Line{false};
    //1.272
    bool isLevel1272Line{false};
    //1.618
    bool isLevel1618Line{false};
    //2.618
    bool isLevel2618Line{false};
    //4.236
    bool isLevel4236Line{false};

};

#endif // FIBONACCILEVELS_H
