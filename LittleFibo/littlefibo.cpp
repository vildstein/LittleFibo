#include "littlefibo.h"
#include "mainwindowscene.h"

#include <QApplication>
#include <QGraphicsView>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QCloseEvent>
#include <QKeySequence>

//Пользовательские ТД
#include "trendline.h"
#include "dot.h"
#include "fibonaccilevels.h"
#include "fibospiral.h"

//Удалить потом
#include <QDebug>


LittleFibo::LittleFibo(QWidget *parent) : QMainWindow(parent)
{
	mScene = new MainWindowScene(this);

	mScene->setSceneRect(QRectF(1000.0, 1000.0, -1000.0, -1000.0));

	mView = new QGraphicsView(mScene, this);
	mView->setDragMode(QGraphicsView::RubberBandDrag);
	mView->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);



	createActions();
	createMenus();
	createStatusBar();

	setCentralWidget(mView);
	setWindowTitle(tr("LittleFiboHelper"));
}

LittleFibo::~LittleFibo()
{

}
//Создать даилог для открыитя файла с торговыми данными
void LittleFibo::createFileDialog()
{

}
//Создать соединение к серваку //Но нужно НАВЕРНОЕ сделать по другому
void LittleFibo::createDataLoadFromNetworkDialog()
{

}
//По хорошему все инструменты, которые имеют 2 точки
//лучше переписать шаблоном

//Создать линию тренда
void LittleFibo::createTrendLine()
{
	auto* trendLine = new TrendLine(mScene);
	mScene->addItem(trendLine);

	//mScene -> addItem(startDot);
	//mScene -> addItem(endDot);
	//mScene->addItem(trendLine);

	//mScene->clearSelection();

}

void LittleFibo::createHorizontalLine()
{

}

void LittleFibo::createVerticalLine()
{


}

void LittleFibo::createFibonacciLevels()
{
//	startDot = new Dot;
//	endDot = new Dot;
//	startDot->setPos(QPointF(150.0, 100.0));
//	endDot->setPos(QPointF(300.0, 300.0));

//	mFibonacciLevels = new FibonacciLevels(startDot, endDot);

//	mScene->addItem(startDot);
//	mScene->addItem(endDot);
//	mScene->addItem(mFibonacciLevels);

//	mScene->clearSelection();
}
//Создать спираль
void LittleFibo::createFibonacciSpiral()
{
	//	startDot = new Dot;
	//	endDot = new Dot;
	//	startDot -> setPos(QPointF(150.0, 150.0));
	//	endDot -> setPos(QPointF(350.0, 350.0));
	//	spiral = new FiboSpiral(startDot, endDot);


	//	mScene -> addItem(startDot);
	//	mScene -> addItem(endDot);
	//	mScene -> addItem(spiral);

	//	mScene -> clearSelection();

}

void LittleFibo::about()
{

}

void LittleFibo::closeEvent(QCloseEvent *event)
{
	saveFile();
	mScene->clear();
	event->accept();
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
	//Экшены для менюшки ФАЙЛ
	readFromFileAction = new QAction(tr("Загрузить данные из файла"), this);

	//А может не надо?
	readFromFileAction -> setStatusTip(tr("Загрузить данные из файла"));

	connectToNetWorkAction = new QAction(tr("Соединиться с сервером"), this);
	connectToNetWorkAction -> setStatusTip(tr("Выбрать биржу и подключиться к ней"));


	exitAction  = new QAction(("Выход"), this);
	exitAction -> setShortcut(tr("Ctrl+Q"));
	exitAction -> setStatusTip(tr("Выход из приложения"));

	//Экшены для менюшки ИНСТРУМЕНТЫ
	//1. Для подменюшки СЕТЬ
	showGridAction = new QAction(tr("Показать сетку"), this);
	showGridAction -> setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
	hideGridAction = new QAction(tr("Скрыть сетку"), this);
	hideGridAction -> setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
	setupGridAction = new QAction(tr("Настроить сетку"), this);

	//2. Для подменюшки Линии
	trendLineAction = new QAction(tr("Создать линию тренда"), this);
	horizontalLineAction = new QAction(tr("Создать горизонтальную линию"), this);
	verticalLineAction = new QAction(tr("Создать вертикальную линию"), this);

	//3. Для подменюшки Инструменты Фибоначчи
	fiboLevelsAction = new QAction(tr("Уровни Фибоначчи"), this);
	fiboExtensionAction = new QAction(tr("Расширения Фибоначчи"), this);
	fiboSpiralAction = new QAction(tr("Спираль Фибоначчи"), this);
	fiboTimeAction = new QAction(tr("Временные зоны фибоначчи"), this);

	//4. Для подменюшки Билл Вильямс
	fractalsAction = new QAction(tr("Фракталы Билла Вильямса"), this);
	alligatorAction = new QAction(tr("Аллигатор"), this);
	amazingOsAction = new QAction(tr("Чудесный осцилятор"), this);
	accelerationDecelerationAction = new QAction(tr("Ускорение/ Замедление"), this);
	//Добавить еще что то там, прочитать


	//5. Для подменюшки Волны Эллиота


	//6. Для подменюшки Индикаторы ТА


	//7. Для подменюшки Графические Символы


	//Экшены для менюшки О ПРОГРАММЕ
	aboutAction = new QAction(("Про LittleFibo"), this);
	aboutQtAction = new QAction(("About Qt"), this);

	//Коннекты для меню "Файл"
	connect(readFromFileAction, &QAction::triggered, this, &LittleFibo::createFileDialog);
	connect(connectToNetWorkAction, &QAction::triggered, this, &LittleFibo::createDataLoadFromNetworkDialog);//
	connect(exitAction, &QAction::triggered, this, &LittleFibo::close);

	//Коннекты для под Меню ЛИНИИ
	connect(trendLineAction, &QAction::triggered, this, &LittleFibo::createTrendLine);
	connect(horizontalLineAction, &QAction::triggered, this, &LittleFibo::createHorizontalLine);
	connect(verticalLineAction, &QAction::triggered, this, &LittleFibo::createVerticalLine);

	//Коннекты для од Меню ИНСТРУМЕНТЫ ФИБОНАЧЧИ
	connect(fiboLevelsAction, &QAction::triggered, this, &LittleFibo::createFibonacciLevels);
	connect(fiboSpiralAction, &QAction::triggered, this, &LittleFibo::createFibonacciSpiral);


	//Коннекты для меню About
	connect(aboutAction, &QAction::triggered, this, &LittleFibo::about);
	connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);

}

void LittleFibo::createMenus()
{
	//Меню файл
	fileMenu = menuBar() -> addMenu(tr("Файл"));
	fileMenu -> addAction(readFromFileAction);
	fileMenu -> addAction(connectToNetWorkAction);
	fileMenu -> addAction(exitAction);

	//1. ПодМеню Сетка
	gridMenu = new QMenu(tr("Сетка"), this);
	gridMenu -> addAction(showGridAction);
	gridMenu -> addAction(hideGridAction);
	gridMenu -> addAction(setupGridAction);

	//2. ПодМеню Линии
	linesMenu = new QMenu(tr("Линии"), this);
	linesMenu -> addAction(trendLineAction);
	linesMenu -> addAction(horizontalLineAction);
	linesMenu -> addAction(verticalLineAction);

	//3. ПодМеню Инструменты Фибоначчи
	fiboToolsMenu = new QMenu(tr("Инструменты Фибоначчи"), this);
	fiboToolsMenu -> addAction(fiboLevelsAction);
	fiboToolsMenu -> addAction(fiboExtensionAction);
	fiboToolsMenu -> addAction(fiboSpiralAction);
	fiboToolsMenu -> addAction(fiboTimeAction);

	//4. Подменю Билл Вильямс
	BillWilliamsMenu = new QMenu(tr("Билл Вильямс"), this);
	BillWilliamsMenu -> addAction(fractalsAction);
	BillWilliamsMenu -> addAction(alligatorAction);
	BillWilliamsMenu -> addAction(amazingOsAction);
	BillWilliamsMenu -> addAction(accelerationDecelerationAction);

	//5. Подменю Волны Эллиота
	ElliottWavesMenu = new QMenu(tr("Волны Эллиота"), this);

	//6. Подменю Индикаторы TA
	technicalAnalysisMenu = new QMenu(tr("Инструменты ТА"), this);

	//7. ПодМеню Графические символы
	graphicSymbolsMenu = new QMenu(tr("Знаки"), this);

	//Меню Инструменты
	toolsMenu = menuBar() -> addMenu(tr("Инструменты"));
	toolsMenu -> addMenu(gridMenu);
	toolsMenu -> addMenu(linesMenu);
	toolsMenu -> addMenu(fiboToolsMenu);
	toolsMenu -> addMenu(BillWilliamsMenu);
	toolsMenu -> addMenu(ElliottWavesMenu);
	toolsMenu -> addMenu(technicalAnalysisMenu);
	toolsMenu -> addMenu(graphicSymbolsMenu);

	//Меню "Опрограмме"
	aboutMenu = menuBar()->addMenu(tr("О программе"));
	aboutMenu -> addAction(aboutAction);
	aboutMenu -> addAction(aboutQtAction);
}

void LittleFibo::createStatusBar()
{

}
