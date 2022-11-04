//
// Created by WhiteNight on 2022/11/1.
//

#include "MyInt.h"

//*********************************************/
/***** ȡ�����ķ���
/***********************************************/
bool MyInt::getSign() {
    // ����
    bool rt = false;
    for (int i = bitCount - 1; i >= 0; i--) {
        if (bit[i] > (R - 1) / 2) {
            // ����
            rt = true;
            break;
        } else if (bit[i] < (R - 1) / 2) {
            // ����
            rt = false;
            break;
        }
    }
    return rt;
}

MyInt::operator MyNumber() {
    MyNumber *p;
    p = (MyNumber *) this;
    // ���ÿ������캯������һ���µĶ���
    return *p;
}

MyInt &MyInt::operator++() {
    MyNumber *p = (MyNumber *) this;
    // ʹ����Ȼ������������
    (*p)++;
    return *this;
}

MyInt MyInt::operator++(int a) {
    MyInt rt;
    rt = *this;
    MyNumber *p = (MyNumber *) this;
    // ʹ����Ȼ������������
    (*p)++;
    return rt;
}

bool MyInt::operator>(MyInt b) {
    bool rt;
    MyInt a;
    a = (*this) - b;
    rt = a.getSign();
    return !rt;
}

//*********************************************/
/***** �����ĸ�ֵ�ͼӷ�
/***********************************************/
MyInt &MyInt::operator=(const MyInt v) {
    const MyNumber *p = (MyNumber *) &v;
    MyNumber *t = (MyNumber *) this;
    (*t) = (*p);
    return *this;
}

MyInt MyInt::operator+(MyInt b) {
    MyInt rt;
    const MyNumber *p = (MyNumber *) &b;
    rt = (*((MyNumber *) this) + (MyNumber) (*p));
    return rt;
}

MyInt MyInt::operator-() {
    MyInt rt;
    for (int i = 0; i < bitCount; i++)
        rt.bit[i] = R - bit[i] - 1;
    // ��1
    rt++;
    return rt;
}

MyInt MyInt::operator-(MyInt b) {
    MyInt rt;
    rt = (*this) + (-b);
    return rt;
}

MyNumber MyInt::getPositive() {
    if (getSign())
        return -(*this);
    else
        return *this;
}

MyInt MyInt::operator*(MyInt b) {
    // �������
    bool sign;
    if (this->getSign() == b.getSign())
        sign = false;
    else
        sign = true;
    // ʹ����Ȼ���ĳ˷�������ֵ
    MyInt rt;
    rt = getPositive() * b.getPositive();
    // ���ӷ���
    if (sign)
        rt = -rt;
    return rt;
}

MyInt MyInt::operator/(MyInt b) {
    if (b.getPositive().isZero()) {
        throw "0����������";
    }
    // �������
    bool flag = true;
    if (this->getSign() == b.getSign())
        flag = false;
    // ȡ���������ֲ���(��Ȼ��)
    MyNumber ua = this->getPositive();
    MyNumber ub = b.getPositive();
    MyInt quotient = ua / ub;
    return flag ? -quotient : quotient;
}

MyInt MyInt::operator%(MyInt b) {
    if (b.getPositive().isZero()) {
        throw "0����������";
    }
    // �������
    bool flag = true;
    if (this->getSign() == b.getSign())
        flag = false;
    // ȡ���������ֲ���(��Ȼ��)
    MyNumber ua = this->getPositive();
    MyNumber ub = b.getPositive();
    MyInt remainder = ua % ub;
    return b.getSign() ? -remainder : remainder;
}

void MyInt::setNum(const char s[]) {
    MyNumber n("0");
    // ���������ķ���
    if (s[0] == '+')
        ((MyNumber *) this)->setNum(s + 1);
    else if (s[0] == '-') {
        n.setNum(s + 1);
        (*this) = -((MyInt) n);
    } else
        ((MyNumber *) this)->setNum(s);
}

char *MyInt::getNum(char s[]) {
    MyInt n;
    if (getSign()) {
        s[0] = '-';
        n = -(*this);
        ((MyNumber *) &n)->getNum(s + 1);
    } else {
        s[0] = '+';
        ((MyNumber *) this)->getNum(s + 1);
    }
    return s;
}

MyInt::MyInt(char s[]) {
    setNum(s);
}

MyInt MyInt::operator<<(MyInt b) {
//    MyNumber t = MyInt();
//    t<<b.bit[0];
//    return MyInt(t);
}

MyInt MyInt::operator>>(MyInt b) {
    MyInt t;
    t = (*(MyNumber *) this << b.bit[0]);
    return t;
}

