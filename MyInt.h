//
// Created by WhiteNight on 2022/11/1.
//

#ifndef RCOMPUTER_MYINT_H
#define RCOMPUTER_MYINT_H

#include "MyNumber.h"

class MyNumber;

class MyInt {
public:
    operator MyNumber();

    // 赋值运算
    MyInt &operator=(const MyInt v);

    MyInt &operator++();

    MyInt operator++(int a);

    MyInt operator-();

    bool getSign();

    MyInt operator-(MyInt b);

    MyNumber getPositive();

    MyInt operator+(MyInt b);

    MyInt operator*(MyInt b);

    MyInt operator/(MyInt b);

    MyInt operator%(MyInt b);

    // 整数的记法与内部存储的转换
    void setNum(const char s[]);

    char *getNum(char s[]);

    MyInt() {};

    MyInt(char s[]);

    bool operator>(MyInt b);

    MyInt operator<<(MyInt b);

    MyInt operator>>(MyInt b);

public:
    Bit bit[bitCount];
};

#endif //RCOMPUTER_MYINT_H