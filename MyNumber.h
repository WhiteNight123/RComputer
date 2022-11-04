//
// Created by WhiteNight on 2022/11/1.
//

#ifndef RCOMPUTER_MYNUMBER_H
#define RCOMPUTER_MYNUMBER_H

const int R = 8; // 指定进制
const int bitCount = 12; // R进制的固定位数
typedef char Bit;
const char aph[] = "0123456789ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

class MyInt;

class MyNumber {
public:
    MyNumber() {};

    MyNumber(char s[]);

    // 按位运算
    MyNumber operator<<(const Bit &b);

    MyNumber operator>>(const Bit &b);

    MyNumber bitAdd(const MyNumber &b);

    MyNumber carryAdd(const MyNumber &b);

    MyNumber operator*(Bit b);

    //赋值运算
    MyNumber &operator=(MyNumber v);

    //自然数据的加法和乘法运算
    bool isZero() const;

    MyNumber operator+(MyNumber b);

    MyNumber operator*(MyNumber b);

    MyNumber operator/(MyNumber b);

    MyNumber operator%(MyNumber b);

    MyNumber &operator++();

    MyNumber operator++(int a);

    MyNumber operator-();

    MyNumber operator-(MyInt b);

    bool operator<(MyNumber b) const;

    bool operator>(MyNumber b) const;

    bool operator==(MyNumber b) const;

    operator MyInt();

    // 自然数记法与内部存储之间的转换
    void setNum(const char s[]);

    char *getNum(char s[]);

public:
    Bit bit[bitCount];
};

#endif //RCOMPUTER_MYNUMBER_H