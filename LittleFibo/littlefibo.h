#ifndef LITTLEFIBO_H
#define LITTLEFIBO_H

#include <QMainWindow>

//Предварительное объявление классов, чтобы не пихать
//Все хедеры в один

class QGraphicsView;
class QAction;
class QMenu;

//Пользовательские ТД
class MainWindowScene;
class Dot;
class TrendLine;
class FibonacciLevels;
class FiboSpiral;


//Сначала прописать класс Bar
//В Меню сделать 2 варианта: загрузить данные из файла
// и подключиться к серваку
//Прочитать торговые данные из файла
//Сохранить торговые данные в файл
//Вывести торговые данные на сцену
//Масштабирование
//Графические инструменты

class LittleFibo : public QMainWindow
{
    Q_OBJECT

public:
    explicit LittleFibo(QWidget *parent = nullptr);
    virtual ~LittleFibo();

    //Геттеры

    //Сеттеры

signals:

public slots:

private slots:
    //Создать даилог для открыитя файла с торговыми данными
    void createFileDialog();
    //Создать соединение к серваку //Но нужно НАВЕРНОЕ сделать по другому
    void createDataLoadFromNetworkDialog();
    //Создать линию тренда
    void createTrendLine();
    //Создать Горизгонтальныую линию
    void createHorizontalLine();
    //Создать Вертикальную линию
    void createVerticalLine();

    //Создать уровни Фибоначчи
    void createFibonacciLevels();

    //Создать спираль
    void createFibonacciSpiral();

    //Окно "О Программе"
    void about();

protected:
    virtual void closeEvent(QCloseEvent *event) override;

private:
    //Функция загрузки данных с которыми работали в последнюю очередь. Вызывается при запуске программы.
    void loadFile();
    void saveFile();

    //Функция загрузки данных из файла текстового или файла приложения
    bool loadDataFromFile();

    //Создать действия(т. е. пункты меню)
    void createActions();
    //Создать меню
    void createMenus();
    //Создать строку состояния
    void createStatusBar();


    QGraphicsView *mView;

    //Пользовательские тд
    MainWindowScene *mScene;

    Dot *startDot;
    Dot *endDot;
    TrendLine *trendLine;
    FibonacciLevels *mFibonacciLevels;
    FiboSpiral *spiral;


    //Экшены для менюшки ФАЙЛ
    QAction *readFromFileAction;
    QAction *connectToNetWorkAction;
    QAction *exitAction;

    //Экшены для менюшки ИНСТРУМЕНТЫ
    //1. Для подменюшки СЕТЬ
    QAction *showGridAction;
    QAction *hideGridAction;
    QAction *setupGridAction;

    //2. Для подменюшки Линии
    QAction *trendLineAction;
    QAction *horizontalLineAction;
    QAction *verticalLineAction;

    //3. Для подменюшки Инструменты Фибоначчи
    QAction *fiboLevelsAction;
    QAction *fiboExtensionAction;
    QAction *fiboSpiralAction;
    QAction *fiboTimeAction;

    //4. Для подменюшки Билл Вильямс
    QAction *fractalsAction;
    QAction *alligatorAction;
    QAction *amazingOsAction;
    QAction *accelerationDecelerationAction;
    //Добавить еще что то там, прочитать


    //5. Для подменюшки Волны Эллиота


    //6. Для подменюшки Индикаторы ТА


    //7. Для подменюшки Графические Символы



    //Экшены для менюшки О ПРОГРАММЕ
    QAction *aboutAction;
    QAction *aboutQtAction;

    //Меню файл
    QMenu *fileMenu;
    //Меню Инструменты
    QMenu *toolsMenu;

    //ПодМенюшки
    //1. ПодМеню Сетка
    QMenu *gridMenu;
    //2. ПодМеню Линии
    QMenu *linesMenu;
    //3. ПодМеню Инструменты Фибоначчи
    QMenu *fiboToolsMenu;
    //4. Подменю Билл Вильямс
    QMenu *BillWilliamsMenu;
    //5. Подменю Волны Эллиота
    QMenu *ElliottWavesMenu;
    //6. Подменю Индикаторы TA
    QMenu *technicalAnalysisMenu;
    //7. ПодМеню Графические символы
    QMenu *graphicSymbolsMenu;

    //Меню "Опрограмме"
    QMenu *aboutMenu;

    //Флаг для функции показать сетку или нет
    bool isGridShown{true};
};
#endif // LITTLEFIBO_H
