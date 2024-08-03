#ifndef TEMPLATES_H
#define TEMPLATES_H

//НэймСпэйс для функций, которые будут часто использоваться
//И писать одно и то же в разных классах смысла нет
namespace Functions {

    void setInvertedBool(bool &value)
    {
        value = !value;
    }

}


#endif // TEMPLATES_H
