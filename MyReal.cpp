//
// Created by WhiteNight on 2022/11/1.
//
#include "MyReal.h"

char *MyReal::getNum(char s[]) {
    MyInt zero("0"), dec;
    int i = 0, j = bitCount - 1;
    if (decimal.getSign()) {
        s[i++] = '-';
        dec = -decimal;
    } else
        dec = decimal;
    if (exponent.getSign()) {
        s[i++] = '0';
        s[i++] = '.';
        while (!(exponent > zero)) {
            s[i++] = '0';
            exponent++;
        }
        while (j >= 0)
            s[i++] = aph[dec.bit[j--]];
    } else {
        // С��������,С�������, ָ�����λ
        int a = bitCount - 1, b = 0, c = 0;
        MyInt tmp;
        // ������λ����
        while (!dec.bit[a]) {
            a--;
            c++;
        }
        // С������1λ����
        while (a >= 0) {
            tmp.bit[a + c] = dec.bit[a];
            a--;
            b++;
        }
        // ���油��
        while (b < bitCount) {
            tmp.bit[bitCount - b - 1] = 0;
            b++;
        }
        dec = tmp;
        MyInt k("0");
        while (!(k > exponent)) {
            s[i++] = aph[dec.bit[j--]];
            k++;
        }
        s[i++] = '.';
        while (j >= 0) {
            s[i++] = aph[dec.bit[j--]];
            k++;
        }
    }
    s[i] = '\0';
    return s;
}

MyReal::MyReal(MyInt d, MyInt e) {
    exponent = e;
    bool sign;
    if (sign = d.getSign()) {
        d = -d;
    };
    // С��������,С�������, ָ�����λ
    int i = bitCount - 1, j = 0;
    // ������λ����
    while (!d.bit[i])
        i--;
    // С������1λ����
    while (i >= 0) {
        decimal.bit[i] = d.bit[i];
        i--;
        j++;
    }
    // ���油��
    while (j < bitCount) {
        decimal.bit[j] = 0;
        j++;
    }
    if (sign) {
        decimal = -decimal;
    }
}

MyReal MyReal::operator+(MyReal b) {
    MyReal rt;
    MyInt exp, a, dec;
    bool flag = false;

    // �ȶ���С���������
    if (exponent > b.exponent) {
        exp = exponent;
        a = b.decimal >> (exponent - b.exponent);
        dec = a + decimal;
    } else {
        exp = b.exponent;
        a = decimal >> (b.exponent - exponent);
        dec = a + b.decimal;
    }
    // ������ʱΪ����
    if (b.decimal.getSign() && dec > (-b.decimal))
        flag = true;
    if (flag)
        dec = -dec;
    rt.exponent = exp;
    rt.decimal = dec;
    return rt;
}

MyReal MyReal::operator-(MyReal b) {
    MyReal rt;
    MyInt exp, a, dec;
    bool flag = false;

    // �ȶ���С���������
    if (exponent > b.exponent) {
        exp = exponent;
        a = b.decimal >> (exponent - b.exponent);
        dec = a - decimal;
    } else {
        exp = b.exponent;
        a = decimal >> (b.exponent - exponent);
        dec = a - b.decimal;
    }
    // �������ڱ�����ʱΪ����
    if (!b.decimal.getSign() && dec > (-b.decimal))
        flag = true;
    if (flag)
        dec = -dec;
    rt.exponent = exp;
    rt.decimal = dec;
    return rt;
}

MyReal MyReal::operator*(MyReal b) {
    MyReal rt;
    rt.exponent = exponent + b.exponent;
    rt.decimal = decimal * b.decimal;
    return rt;
}