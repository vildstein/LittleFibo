#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <QVector>
#include <QMap>

//НэймСпэйс для функций, которые будут часто использоваться
//И писать одно и то же в разных классах смысла нет
namespace Functions {

void setInvertedBool(bool &value)
{
	value = !value;
}

void setBoolValueTrue(bool &value)
{
	value = true;
}

void setBoolValueFalse(bool &value)
{
	value = false;
}


}

namespace TemplatesFunctions {

template<typename T>
void clearVector(QVector<T> &vector)
{
	if (!vector.isEmpty()) {
		vector.clear();
	}
}


//Плохо работатет
//Нужно доработать
template <typename T>
void clearDynamicVector(QVector<T*> &vector)
{
	if (!vector.isEmpty()) {
		class QVector<T*>::iterator i;
		for(i = vector.begin(); i !=vector.end(); ++i) {
			delete *i;
			*i=nullptr;
		}
		vector.clear();
	}
}

template <typename T1, typename T2>
void clearDynamicMap(QMap<T1, T2*> &mainMap)
{
	if (!mainMap.isEmpty()) {
		class QMap<T1, T2*>::iterator it;
		for(it = mainMap.begin(); it != mainMap.end(); it++) {
			delete it.value();
			it.value() = nullptr;
		}
		mainMap.clear();
	}
}

}


#endif // TEMPLATES_H
