#ifndef MAINWINDOWSCENE_H
#define MAINWINDOWSCENE_H

#include <QGraphicsScene>

class MainWindowScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MainWindowScene(QObject *parent = nullptr);
    virtual ~MainWindowScene();
};

#endif // MAINWINDOWSCENE_H
