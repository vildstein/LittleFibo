#ifndef DOT_H
#define DOT_H

#include <QGraphicsObject>

class TrendLine;

class Dot : public QGraphicsObject
{
public:
    Dot(QGraphicsItem *parent = nullptr);
    virtual ~Dot() = default;

    //Геттеры

    //Сеттеры
    void setLine(TrendLine *trendLine);

protected:
    virtual QRectF	boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    //QPointF mPos;
    QPointF mCenter{0, 0};
    QRectF mItemRect;

    TrendLine *mTrendLine;
};

#endif // DOT_H
