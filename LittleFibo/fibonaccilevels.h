#ifndef FIBONACCILEVELS_H
#define FIBONACCILEVELS_H

#include <QGraphicsLineItem>
class Dot;

class FibonacciLevels : public QGraphicsLineItem
{
public:
    FibonacciLevels(Dot *startPos = nullptr, Dot *endPos = nullptr, QGraphicsItem *parent = nullptr);
    virtual ~FibonacciLevels();

    void updatePosition();
    //Геттеры

    //Сеттеры

protected:
    //virtual QRectF boundingRect() const override;
    //virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    //virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    //virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
    //virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    //virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
    Dot *mStartPosDot;
    Dot *mEndPosDot;
    QLineF *mMainLine;

    QLineF *mLevelLine;
};

#endif // FIBONACCILEVELS_H
