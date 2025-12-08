#ifndef TRENDLINE_H
#define TRENDLINE_H

#include <QGraphicsLineItem>

class QAction;
class Dot;
class  MainWindowScene;
//class Line;
//class QActionGroup;

//Контест Меню Ивент

//Прописать диалог на измененеия цвета линни, долщины, и пр


//Описание класса Линия Тренда
class TrendLine : public QGraphicsLineItem//public QGraphicsObject
{
    //Q_OBJECT
public:
    explicit TrendLine(Dot* startPos = nullptr, Dot* endPos = nullptr, MainWindowScene* scene = nullptr, QGraphicsItem* parent = nullptr);
	explicit TrendLine(MainWindowScene* scene = nullptr, QGraphicsItem* parent = nullptr);
	virtual ~TrendLine();

    void updatePosition();

	//Геттеры
	QPointF getStartPos() const;

	//Сеттеры

signals:
	void deleteMe();

protected:
	virtual QRectF boundingRect() const override;
	virtual QPainterPath shape() const override;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    //virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
	void createActions();
	void createMenues();

    Dot*  m_StartPosDot{nullptr};
    Dot*  m_EndPosDot{nullptr};
    //QScopedPointer<Dot> mStartPosDot;
    //std::unique_ptr<Dot> mStartPosDot;
    //QScopedPointer<Dot> mEndPosDot;
	QScopedPointer<QLineF> mLine;

	//QLineF* mLine;

	MainWindowScene* mScene{nullptr};
    //QActionGroup *menuActionGroup = nullptr;
	QAction* settingsAction;
	QAction* deleteAction;

	//Dot *mStartPosDot;
	//Dot *mEndPosDot;
	//QLineF mLine;
};
#endif // TRENDLINE_H
