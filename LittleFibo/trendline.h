#ifndef TRENDLINE_H
#define TRENDLINE_H

#include <QGraphicsLineItem>

class QAction;
class Dot;
class Line;
//class QActionGroup;

//Контест Меню Ивент

//Прописать диалог на измененеия цвета линни, долщины, и пр


//Описание класса Линия Тренда
class TrendLine : public QGraphicsObject
{
	Q_OBJECT
public:
	explicit TrendLine(const QPointF& startPos, const QPointF& endPos, QGraphicsItem *parent = nullptr);
	virtual ~TrendLine();

	//void updatePosition();

	//Геттеры
	QPointF getStartPos() const;

	//Сеттеры

signals:
	void deleteMe();

protected:
	virtual QRectF boundingRect() const override;
	virtual QPainterPath shape() const override;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	//virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
	virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
	void createActions();
	void createMenues();

	QScopedPointer<Dot> mStartPosDot;
	QScopedPointer<Dot> mEndPosDot;
	QScopedPointer<Line> mLine;

	//QActionGroup *menuActionGroup = nullptr;
	QAction* settingsAction;
	QAction* deleteAction;

	//Dot *mStartPosDot;
	//Dot *mEndPosDot;
	//QLineF mLine;
};

// Описание класса Line. Потом перенсу в другой файл

class Line : public QGraphicsLineItem
{
public:
	explicit Line(Dot* startDot, Dot* endDot, QGraphicsLineItem *parent = nullptr);
	explicit Line(const QPointF&  startPos, const QPointF& endPos, QGraphicsLineItem *parent = nullptr);
	virtual ~Line() = default;

	void updatePosition();

protected:
	virtual QRectF boundingRect() const override;
	virtual QPainterPath shape() const override;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
	Dot* mStartDot = nullptr;
	Dot* mEndDot = nullptr;
	QPointF mStartPos{0.0, 0.0};
	QPointF mEndPos{0.0, 0.0};
	QLineF mLine;
};

#endif // TRENDLINE_H
