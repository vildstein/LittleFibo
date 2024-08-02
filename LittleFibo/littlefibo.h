#ifndef LITTLEFIBO_H
#define LITTLEFIBO_H

#include <QMainWindow>

class QGraphicsView;
class MainWindowScene;

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

protected:

private:
    QGraphicsView *mView;
    MainWindowScene *mScene;

};
#endif // LITTLEFIBO_H
