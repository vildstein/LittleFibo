#ifndef DOT_H
#define DOT_H

#include <QGraphicsObject>

class TrendLine;
class FiboSpiral;
class FibonacciLevels;

class Dot : public QGraphicsEllipseItem//public QGraphicsObject
{
public:
	explicit Dot(QGraphicsEllipseItem *parent = nullptr);
	explicit Dot(const QPointF& pos, QGraphicsEllipseItem *parent = nullptr);
	virtual ~Dot() = default;

	void updateStartPosition(TrendLine *trendLine = nullptr);
	void updateEndPosition(TrendLine *trendLine = nullptr);

	//Геттеры
	QPointF getCenter() const;

	//Сеттеры
    void setLine(TrendLine* trendLine = nullptr);
    void setSpiral(FiboSpiral* spiral = nullptr);
    void setFibonacciLevelsMainLine(FibonacciLevels* mainLine = nullptr);

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

    TrendLine* mTrendLine = nullptr;
    FiboSpiral* mSpiral = nullptr;
    FibonacciLevels* mFibonacciLevelsMainLine = nullptr;
};

#endif // DOT_H
