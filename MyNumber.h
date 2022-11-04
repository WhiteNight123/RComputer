//
// Created by WhiteNight on 2022/11/1.
//

#ifndef RCOMPUTER_MYNUMBER_H
#define RCOMPUTER_MYNUMBER_H

const int R = 8; // ָ������
const int bitCount = 12; // R���ƵĹ̶�λ��
typedef char Bit;
const char aph[] = "0123456789ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

class MyInt;

class MyNumber {
public:
    MyNumber() {};

    MyNumber(char s[]);

    // ��λ����
    MyNumber operator<<(const Bit &b);

    MyNumber operator>>(const Bit &b);

    MyNumber bitAdd(const MyNumber &b);

    MyNumber carryAdd(const MyNumber &b);

    MyNumber operator*(Bit b);

    //��ֵ����
    MyNumber &operator=(MyNumber v);

    //��Ȼ���ݵļӷ��ͳ˷�����
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

    // ��Ȼ���Ƿ����ڲ��洢֮���ת��
    void setNum(const char s[]);

    char *getNum(char s[]);

public:
    Bit bit[bitCount];
};

#endif //RCOMPUTER_MYNUMBER_H