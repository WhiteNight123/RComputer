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
        // 小数点在左,小数左对齐, 指向最高位
        int a = bitCount - 1, b = 0, c = 0;
        MyInt tmp;
        // 跳过高位的零
        while (!dec.bit[a]) {
            a--;
            c++;
        }
        // 小数点后第1位非零
        while (a >= 0) {
            tmp.bit[a + c] = dec.bit[a];
            a--;
            b++;
        }
        // 后面补零
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
    // 小数点在左,小数左对齐, 指向最高位
    int i = bitCount - 1, j = 0;
    // 跳过高位的零
    while (!d.bit[i])
        i--;
    // 小数点后第1位非零
    while (i >= 0) {
        decimal.bit[i] = d.bit[i];
        i--;
        j++;
    }
    // 后面补零
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

    // 先对其小数点再相加
    if (exponent > b.exponent) {
        exp = exponent;
        a = b.decimal >> (exponent - b.exponent);
        dec = a + decimal;
    } else {
        exp = b.exponent;
        a = decimal >> (b.exponent - exponent);
        dec = a + b.decimal;
    }
    // 负数大时为负号
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

    // 先对其小数点再相加
    if (exponent > b.exponent) {
        exp = exponent;
        a = b.decimal >> (exponent - b.exponent);
        dec = a - decimal;
    } else {
        exp = b.exponent;
        a = decimal >> (b.exponent - exponent);
        dec = a - b.decimal;
    }
    // 减数大于被减数时为负号
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