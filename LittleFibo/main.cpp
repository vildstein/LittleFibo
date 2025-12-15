#include "littlefibo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LittleFibo* littleFibo = new LittleFibo;
	littleFibo->showMaximized();
	auto result = a.exec();

	delete littleFibo;
	return result;
}
