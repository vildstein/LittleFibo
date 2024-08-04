#ifndef TRENDLINE_H
#define TRENDLINE_H

#include <QGraphicsLineItem>
class Dot;


//Переопредлить функции:



//Контест Меню Ивент

//Прописать диалог на измененеия цвета линни, долщины, и пр


//Описание класса Линия Тренда
class TrendLine : public QGraphicsLineItem
{
public:
    TrendLine(Dot *startPos, Dot *endPos, QGraphicsItem *parent = nullptr);

    void updatePosition();

    //Геттеры

    //Сеттеры

//signals:

protected:
    //virtual QRectF boundingRect() const override;
    //virtual QPainterPath shape() const override;
    //virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    //virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    //virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
    Dot *mStartPosDot;
    Dot *mEndPosDot;
};

#endif // TRENDLINE_H
