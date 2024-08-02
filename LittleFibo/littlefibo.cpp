#include "littlefibo.h"
#include "mainwindowscene.h"

#include <QGraphicsView>

LittleFibo::LittleFibo(QWidget *parent)
    : QMainWindow(parent)
{
    mScene = new MainWindowScene(this);
    mView = new QGraphicsView(mScene, this);

    setCentralWidget(mView);
}

LittleFibo::~LittleFibo()
{

}
