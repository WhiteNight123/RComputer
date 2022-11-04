//
// Created by WhiteNight on 2022/11/1.
//

#include "MyNumber.h"
#include <cstring>
#include "MyInt.h"
//**************************************/
/*****λ������
/*****************************/
MyNumber MyNumber::operator<<(const Bit &b) {
    MyNumber rt("0");
    int i = 0, j = 0;
    while (i < b) {
        rt.bit[i] = 0;
        i++;
    }
    while (i < bitCount) {
        rt.bit[i] = bit[j];
        i++;
        j++;
    }
    return rt;
}

MyNumber MyNumber::operator>>(const Bit &b) {
    MyNumber rt("0");
    int i = 0, j = b;
    while (i < bitCount - b) {
        rt.bit[i] = bit[j];
        i++;
        j++;
    }
    while (i < bitCount) {
        rt.bit[i] = 0;
        i++;
    }
    return rt;
}

//*************************************/
//*****�ӷ�����
/*************************************/
// ��λ��Ӳ���λ
MyNumber MyNumber::bitAdd(const MyNumber &b) {
    MyNumber t("0");
    for (int i = 0; i < bitCount; i++)
        // ��λ���,��ͨ���ӷ��ھ���ʵ��
        t.bit[i] = (bit[i] + b.bit[i]) % R;
    return t;
}

// �����λ������һλ
MyNumber MyNumber::carryAdd(const MyNumber &b) {
    MyNumber t("0");
    t.bit[0] = 0;
    for (int i = 0; i < bitCount - 1; i++)
        t.bit[i + 1] = (bit[i] + b.bit[i]) / R;
    return t;
}

// �ж�һ����Ȼ���Ƿ�Ϊ0
bool MyNumber::isZero() const {
    bool flag = true;
    for (int i = 0; i < bitCount; i++) {
        if (bit[i]) {
            flag = false;
            break;
        }
    }
    return flag;
}

MyNumber MyNumber::operator+(MyNumber b) {
    MyNumber sum("0"), carry("0");
    if (b.isZero())
        return *this;
    // ��λ��ӵ�����λ
    sum = bitAdd(b);
    // �����λ������һλ
    carry = carryAdd(b);
    // �ӽ�λ
    return sum.operator+(carry);
}

MyNumber MyNumber::operator-() {
    MyNumber rt;
    for (int i = 0; i < bitCount; i++)
        rt.bit[i] = R - bit[i] - 1;
    // ��1
    rt++;
    return rt;
}

MyNumber MyNumber::operator-(MyInt b) {
    MyNumber rt;
    rt = (*this) + (-b);
    return rt;
}
//*********************************************/
/***** �˷�����
/***********************************************/
MyNumber MyNumber::operator*(Bit b) {
    MyNumber rt("0");
    Bit c = 0;
    for (int i = 0; i < bitCount; i++) {
        // ��λ���,��ͨ���˷��ھ���ʵ��
        rt.bit[i] = (bit[i] * b + c) % R;
        c = (bit[i] * b + c) / R;
    }
    return rt;
}

MyNumber MyNumber::operator*(MyNumber b) {
    MyNumber rt("0"), n("0");
    rt = (*this) * b.bit[0];
    for (int i = 1; i < bitCount; i++) {
        if (bit[i]) {
            n = (*this) * b.bit[i];
            rt = rt + (n << i);
        }
    }
    return rt;
}

//*********************************************/
/***** ��������
/***********************************************/

MyNumber MyNumber::operator/(MyNumber b) {
    if (b.isZero()) {
        throw "0����������";
    }
    MyNumber quotient = MyNumber("0");
    MyNumber tmp = MyNumber("1");
    // ȡ���������ֲ���(��Ȼ��)
    MyNumber ua = *this;
    MyNumber ub = b;
    for (int i = bitCount - 1; i >= 0; i--) {
        while ((ua >> i) > ub) {
            quotient = quotient + (tmp << i);
            ua = ua - (ub << i);
        }
    }
    return quotient;
}

MyNumber MyNumber::operator%(MyNumber b) {
    if (b.isZero()) {
        throw "0����������";
    }
    MyNumber quotient = MyNumber("0");
    MyNumber tmp = MyNumber("1");
    // ȡ���������ֲ���(��Ȼ��)
    MyNumber ua = *this;
    MyNumber ub = b;
    for (int i = bitCount - 1; i >= 0; i--) {
        while ((ua >> i) > ub) {
            quotient = quotient + (tmp << i);
            ua = ua - (ub << i);
        }
    }
    return ua;
}

bool MyNumber::operator>(const MyNumber b) const {
    MyInt *ap, *bp, t;
    ap = (MyInt *) this;
    bp = (MyInt *) &b;
    t = *bp - *ap;
    return t.getSign();
}

bool MyNumber::operator<(const MyNumber b) const {
    MyInt *ap, *bp;
    ap = (MyInt *) this;
    bp = (MyInt *) &b;
    return (*ap - *bp).getSign();
}

bool MyNumber::operator==(const MyNumber b) const {
    MyInt *ap, *bp;
    ap = (MyInt *) this;
    bp = (MyInt *) &b;
    return ((MyNumber) (*ap - *bp)).isZero();
}

//*********************************************/
/***** ��������
/***********************************************/
MyNumber &MyNumber::operator++() {
    // ��λ
    Bit c = 0;
    int i = 0;
    c = (bit[i] + 1) / R;
    bit[i] = (bit[i] + 1) % R;
    i++;
    // �ӽ�λ
    while (i < bitCount && c) {
        // �洢��ʱ��λ
        Bit t = c;
        c = (bit[i] + c) / R;
        bit[i] = (bit[i] + t) % R;
        i++;
    }
    // ���ر���(����)
    return *this;
}

MyNumber MyNumber::operator++(int a) {
    MyNumber rt("0");
    rt = *this;
    // ��λ
    Bit c = 0;
    int i = 0;
    c = (bit[i] + 1) / R;
    bit[i] = (bit[i] + 1) % R;
    i++;
    // �ӽ�λ
    while (i < bitCount && c) {
        // �洢��ʱ��λ
        Bit t = c;
        c = (bit[i] + c) / R;
        bit[i] = (bit[i] + t) % R;
        i++;
    }
    // ���ر���(����)��ֵ
    return rt;
}

//*********************************************/
/***** ��Ȼ���Ƿ����ڲ��洢֮���ת��
/***********************************************/
void MyNumber::setNum(const char s[]) {
    int i = strlen(s) - 1, j = 0;
    while ((i >= 0) && (j < bitCount)) {
        if ((s[i] >= 'A') && (s[i] <= 'Z'))
            bit[j] = (s[i] - 'A' + 10) % R;
        else if ((s[i] >= 'a') && (s[i] <= 'z'))
            bit[j] = (s[j] - 'a' + 10) % R;
        else if ((s[i] >= '0') && (s[i] <= '9'))
            bit[j] = (s[i] - '0') % R;
        else
            bit[j] = 0;
        i--;
        j++;
    }
    while (j < bitCount) {
        bit[j] = 0;
        j++;
    }
}

char *MyNumber::getNum(char s[]) {
    for (int i = 0; i < bitCount; i++)
        s[i] = aph[bit[bitCount - i - 1]];
    s[bitCount] = 0;
    return s;
}

MyNumber &MyNumber::operator=(MyNumber v) {
    for (int i = 0; i < bitCount; i++)
        bit[i] = v.bit[i];
    return *this;
}

MyNumber::operator MyInt() {
    MyInt *p;
    p = (MyInt *) this;
    // ���ÿ������캯������һ���µĶ���
    return *p;
}

MyNumber::MyNumber(char s[]) {
    setNum(s);
}