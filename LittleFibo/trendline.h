#ifndef TRENDLINE_H
#define TRENDLINE_H

#include <QGraphicsLineItem>
class Dot;

//Контест Меню Ивент

//Прописать диалог на измененеия цвета линни, долщины, и пр


//Описание класса Линия Тренда
class TrendLine : public QGraphicsLineItem
{
public:
    explicit TrendLine(Dot *startPos, Dot *endPos, QGraphicsItem *parent = nullptr);

    void updatePosition();

    //Геттеры
    QPointF getStartPos() const;

    //Сеттеры

//signals:

protected:
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    //virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
    Dot *mStartPosDot;
    Dot *mEndPosDot;
    QLineF mLine;
};

#endif // TRENDLINE_H
