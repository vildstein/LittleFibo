#ifndef TRENDLINE_H
#define TRENDLINE_H

#include <QGraphicsLineItem>
#include <QCoreApplication>

//class QAction;
class Dot;
class MainWindowScene;
//class Line;
//class QActionGroup;
class QMenu;

//Контест Меню Ивент

//Прописать диалог на измененеия цвета линни, долщины, и пр


//Описание класса Линия Тренда
class TrendLine : public QGraphicsLineItem//public QGraphicsObject
{
	//Q_DECLARE_TR_FUNCTIONS(TrendLine)
public:
	explicit TrendLine(MainWindowScene* scene = nullptr, QGraphicsItem* parent = nullptr);
	virtual ~TrendLine();

	void updatePosition();

	//Геттеры
	QPointF getStartPos() const; //?? Наверное лучше удалить

	//Сеттеры
	void setMenuToOwn(QMenu* contextMenu);

signals:
	void deleteMe();

protected:
	virtual QRectF boundingRect() const override;
	virtual QPainterPath shape() const override;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	//virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
	void createActions();
	//void createMenues();

	Dot*  mStartPosDot{nullptr};
	Dot*  mEndPosDot{nullptr};
	//QScopedPointer<Dot> mStartPosDot;
	//std::unique_ptr<Dot> mStartPosDot;
	//QScopedPointer<Dot> mEndPosDot;
	QScopedPointer<QLineF> mLine;

	//QLineF* mLine;

	MainWindowScene* mScene{nullptr};
	QScopedPointer<QMenu> mContextMenu;
	//QActionGroup *menuActionGroup = nullptr;
	//QAction* settingsAction;
	//QAction* deleteAction;

	//Dot *mStartPosDot;
	//Dot *mEndPosDot;
	//QLineF mLine;
};
#endif // TRENDLINE_H
