#ifndef FIBOSPIRAL_H
#define FIBOSPIRAL_H

#include <QGraphicsPathItem>
#include <QGraphicsLineItem>
#include <QMap>

class Dot;

class FiboSpiral : public QGraphicsPathItem//, private QGraphicsLineItem
{
public:
    explicit FiboSpiral(Dot *startPos, Dot *endPos, QGraphicsItem *parent = nullptr);
    virtual ~FiboSpiral();

    void updatePosition();


    //Геттеры


    //Сеттеры

protected:
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    //virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    //virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
    Dot *mStartPosDot;
    Dot *mEndPosDot;

    QPainterPath *mPath;
    QMap<int, QPointF> mPathMap;
    //QLineF mLine;

};

#endif // FIBOSPIRAL_H
