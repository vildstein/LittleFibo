#include "littlefibo.h"
#include "mainwindowscene.h"

#include <QApplication>
#include <QGraphicsView>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QCloseEvent>



//Удалить потом
#include <QDebug>


LittleFibo::LittleFibo(QWidget *parent)
    : QMainWindow(parent)
{
    mScene = new MainWindowScene(this);
    mView = new QGraphicsView(mScene, this);

    createActions();
    createMenus();

    setCentralWidget(mView);
    setWindowTitle(tr("LittleFiboHelper"));
}

LittleFibo::~LittleFibo()
{

}

void LittleFibo::createFileDialog()
{

}

void LittleFibo::createDataLoadFromNetworkDialog()
{

}

void LittleFibo::about()
{

}

void LittleFibo::closeEvent(QCloseEvent *event)
{
    saveFile();
    event -> accept();

}

void LittleFibo::loadFile()
{

}

void LittleFibo::saveFile()
{

}
//Пока так. Доделать.
bool LittleFibo::loadDataFromFile()
{
    return true;

}

void LittleFibo::createActions()
{
    readFromFileAction = new QAction(tr("Загрузить данные из файла"), this);

    connectToNetWorkAction = new QAction(tr("Соединиться с сервером"), this);

    exitAction  = new QAction(("Выход"), this);

    aboutAction = new QAction(("Про LittleFibo"), this);
    aboutQtAction = new QAction(("About Qt"), this);

    //Коннекты для меню "Файл"
    connect(readFromFileAction, &QAction::triggered, this, &LittleFibo::createFileDialog);
    connect(connectToNetWorkAction, &QAction::triggered, this, &LittleFibo::createDataLoadFromNetworkDialog);//
    connect(exitAction, &QAction::triggered, this, &LittleFibo::close);
    //Коннекты для меню About
    connect(aboutAction, &QAction::triggered, this, &LittleFibo::about);
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);


}

void LittleFibo::createMenus()
{
    fileMenu = menuBar() -> addMenu(tr("Файл"));
    fileMenu -> addAction(readFromFileAction);
    fileMenu -> addAction(connectToNetWorkAction);
    fileMenu -> addAction(exitAction);

    aboutMenu = menuBar() -> addMenu(tr("О программе"));
    aboutMenu -> addAction(aboutAction);
    aboutMenu -> addAction(aboutQtAction);
}
