#ifndef LITTLEFIBO_H
#define LITTLEFIBO_H

#include <QMainWindow>

class QGraphicsView;
class MainWindowScene;
class QAction;
class QMenu;

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
    LittleFibo(QWidget *parent = nullptr);
    virtual ~LittleFibo();

    //Геттеры

    //Сеттеры

signals:

public slots:

private slots:
    void createFileDialog();
    void createDataLoadFromNetworkDialog();
    void about();

protected:
    virtual void closeEvent(QCloseEvent *event) override;

private:
    //Функция загрузки данных с которыми работали в последнюю очередь. Вызывается при запуске программы.
    void loadFile();
    void saveFile();

    //Функция загрузки данных из файла текстового или файла приложения
    bool loadDataFromFile();

    void createActions();
    void createMenus();

    QGraphicsView *mView;
    MainWindowScene *mScene;

    QAction *readFromFileAction;
    QAction *connectToNetWorkAction;
    QAction *exitAction;

    QAction *aboutAction;
    QAction *aboutQtAction;

    QMenu *fileMenu;
    QMenu *aboutMenu;
};
#endif // LITTLEFIBO_H
