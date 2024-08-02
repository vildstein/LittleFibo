#ifndef BAR_H
#define BAR_H

#include <QGraphicsObject>

class Bar : public QGraphicsObject
{
public:
    Bar();
    virtual ~Bar();
    //Геттеры

    //Сеттеры

signals:

public slots:

private slots:

protected:

private:
    double mOpenPrise;
    double mClosePrise;
    double mHightPrise;
    double mLowPrise;
};

#endif // BAR_H
