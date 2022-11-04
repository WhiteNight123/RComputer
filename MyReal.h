//
// Created by WhiteNight on 2022/11/1.
//
#ifndef RCOMPUTER_MYREAL_H
#define RCOMPUTER_MYREAL_H

#include "MyInt.h"

class MyReal {
public:
    MyReal operator+(MyReal b);

    MyReal operator-(MyReal b);

    MyReal operator*(MyReal b);

    MyReal(MyInt d, MyInt e);

    MyReal() {};

    char *getNum(char s[]);

public:
    // С��
    MyInt decimal;
    // ָ��
    MyInt exponent;
};

#endif //RCOMPUTER_MYREAL_H
