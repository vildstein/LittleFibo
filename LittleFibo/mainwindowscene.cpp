#include "mainwindowscene.h"

MainWindowScene::MainWindowScene(QObject *parent) : QGraphicsScene(parent)
{

}

MainWindowScene::~MainWindowScene()
{

}

void MainWindowScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    clear();
}
