#ifndef MAINWINDOWSCENE_H
#define MAINWINDOWSCENE_H

#include <QGraphicsScene>

class MainWindowScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit MainWindowScene(QObject *parent = nullptr);
	virtual ~MainWindowScene();
signals:

public slots:

private slots:

protected:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:


};

#endif // MAINWINDOWSCENE_H
