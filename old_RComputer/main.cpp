#include <iostream>

using namespace std;

const int R = 16; // ָ������
const int bitCount = 4; // R���ƵĹ̶�λ��

/******************************************************************/
/*****��Ȼ����R���Ƽ�����
/******************************************************************/
struct myNumber {
    char bit[bitCount]; // ����"λ"
};

/******************************************************************/
/*****λ��ε�����
/******************************************************************/

// �ж�һ����Ȼ���Ƿ�Ϊ0
bool isZero(const myNumber &a) {
    bool flag = true;
    for (char i: a.bit) {
        if (i) {
            flag = false;
            break;
        }
    }
    return flag;
}

// ȡ����,aΪ��������true
bool getSign(const myNumber &a) {
    return a.bit[0] >= R / 2;
}

// �ȴ�С,a>=b����true
bool compare(const myNumber &a, const myNumber &b) {
    bool flag = true;
    for (int i = 0; i < bitCount; i++) {
        if (a.bit[i] > b.bit[i])
            break;
        else if (a.bit[i] < b.bit[i]) {
            flag = false;
            break;
        }
    }
    return flag;
}

// ��λȡ��
myNumber shiftReverse(const myNumber &a) {
    myNumber t;
    for (int i = 0; i < bitCount; i++)
        t.bit[i] = R - a.bit[i] - 1;
    return t;
}

// ����nλ
myNumber shiftLeft(const myNumber &a, int n) {
    if (n == 0)
        return a;
    myNumber t;
    for (int i = n; i < bitCount; i++)
        t.bit[i - n] = a.bit[i];
    for (int i = 1; i <= n; i++)
        t.bit[bitCount - i] = 0;
    return t;
}

// ����1λ
myNumber shiftLeft(const myNumber &a) {
    return shiftLeft(a, 1);
}

// ����nλ
myNumber shiftRight(const myNumber &a, int n) {
    if (n == 0)
        return a;
    myNumber t;
    for (int i = bitCount - 1; i >= n; i--)
        t.bit[i] = a.bit[i - n];
    for (int i = 0; i < n; i++)
        t.bit[i] = 0;
    return t;
}

// ����1λ
myNumber shiftRight(const myNumber &a) {
    return shiftRight(a, 1);
}

// ����һ���յ�����
myNumber newZeroNumber() {
    myNumber t;
    for (char &i: t.bit)
        i = 0;
    return t;
}

// ����һ��ֵΪ1������
myNumber newOneNumber() {
    myNumber t;
    t = newZeroNumber();
    t.bit[bitCount - 1] = 1;
    return t;
}

// �����λ������һλ
myNumber carryAdd(const myNumber &a, const myNumber &b) {
    myNumber t;
    for (int i = 1; i < bitCount; i++)
        t.bit[i - 1] = (a.bit[i] + b.bit[i]) / R;
    t.bit[bitCount - 1] = 0;
    return t;
}

// ��λ��ӵ�����λ
myNumber bitAdd(const myNumber &a, const myNumber &b) {
    myNumber t;
    for (int i = 0; i < bitCount; i++)
        t.bit[i] = (a.bit[i] + b.bit[i]) % R;
    return t;
}
/******************************************************************/
/*****�����Ӽ��˳�
/******************************************************************/
// ��Ȼ���ӷ�
myNumber add(const myNumber &a, const myNumber &b) {
    myNumber sum, carry;
    if (isZero(b))
        return a;
    sum = bitAdd(a, b); // ��λ��Ӳ���λ
    carry = carryAdd(a, b); // �����λ������һλ
    return add(sum, carry); // �ӽ�λ
}

// ����
myNumber unaryMinus(const myNumber &a) {
    myNumber ui, tmp;
    ui = shiftReverse(a);
    tmp = newOneNumber();
    return add(ui, tmp);
}

// ����
myNumber substract(const myNumber &a, const myNumber &b) {
    return add(a, unaryMinus(b));
}

// ȡ��Ȼ��
myNumber getPositive(const myNumber &a) {
    return getSign(a) ? unaryMinus(a) : a;
}

// �˷�
myNumber multiply(const myNumber &a, const myNumber &b) {
    // �������
    bool flag = true;
    if (getSign(a) == getSign(b))
        flag = false;
    myNumber ua, ub, res /**,tmp*/;
    res = newZeroNumber();
    //tmp = newOneNumber();
    // ȡ���������ֲ���(��Ȼ��)
    ua = getPositive(a);
    ub = getPositive(b);
    // ����Ȼ���˷��������ֲ���
    while (!isZero(ub)) {
//        // ��ѧ����ʵ��
//        res = add(res, ua);
//        ub = substract(ub, tmp);
        for (int i = 0; i < ub.bit[bitCount - 1]; i++)
            res = add(res, ua);
        // ��ua��λ���ڻ���
        ua = shiftLeft(ua);
        // �����λ��ʼ�����ж�b��ÿһλ
        ub = shiftRight(ub);
    }
    return flag ? unaryMinus(res) : res;
}

// ����
myNumber *divide1(const myNumber &a, const myNumber &b, myNumber arr[2]) {
    if (isZero(b)) {
        cout << "0����������" << endl;
        return arr;
    }
    // �������
    bool flag = true;
    if (getSign(a) == getSign(b))
        flag = false;
    myNumber ua, ub, quotient, remainder, tmp;
    quotient = newZeroNumber();
    tmp = newOneNumber();
    // ȡ���������ֲ���(��Ȼ��)
    ua = getPositive(a);
    ub = getPositive(b);
    for (int i = bitCount - 1; i >= 0; i--) {
        while (compare(shiftRight(ua, i), ub)) {
            quotient = add(quotient, shiftLeft(tmp, i));
            ua = substract(ua, shiftLeft(ub, i));
        }
    }
//    // ��ѧ����ʵ��
//    while (compare(ua, ub)) {
//        quotient = add(quotient, tmp);
//        ua = substract(ua, ub);
//    }
    quotient = flag ? unaryMinus(quotient) : quotient;
    remainder = getSign(b) ? unaryMinus(ua) : ua;
    arr[0] = quotient;
    arr[1] = remainder;
    return arr;
}

// ����
myNumber divide(const myNumber &a, const myNumber &b) {
    myNumber *arr = new myNumber[2];
    arr = divide1(a, b, arr);
    return arr[0];
}

// ��ģ
myNumber mod(const myNumber &a, const myNumber &b) {
    myNumber *arr = new myNumber[2];
    arr = divide1(a, b, arr);
    return arr[1];
}
/******************************************************************/
/*****�ڲ��������ⲿ�����໥ת������
/******************************************************************/
void setNum(myNumber &a, const char *v) {
    for (int i = 0; i < bitCount; i++) {
        if ((v[i] >= 'A') && (v[i] <= 'Z'))
            a.bit[i] = (v[i] - 'A' + 10) % R;
        else if ((v[i] >= 'a') && (v[i] <= 'z'))
            a.bit[i] = (v[i] - 'a' + 10) % R;
        else if ((v[i] >= '0') && (v[i] <= '9'))
            a.bit[i] = (v[i] - '0') % R;
        else
            a.bit[i] = 0;
    }
}

const char aph[] = "0123456789ABCDEFGHIGKLMNOPQRSTUVWXYZ";

char *getNum(const myNumber &a) {
    char *t = new char[bitCount + 1];
    for (int i = 0; i < bitCount; i++)
        t[i] = aph[a.bit[i]];
    t[bitCount] = 0;
    return t;
}

/******************************************************************/
/*****Ӧ�ò�
/******************************************************************/
int main() {
    myNumber a, b, c;
    char Buffer[30];
    cout << "��������" << R << "���ڵ�" << bitCount << "λ��." << endl;
    cout << "�������һ��:";
    cin >> Buffer;
    setNum(a, Buffer);
    cout << "������ڶ���:";
    cin >> Buffer;
    setNum(b, Buffer);
    cout << "aΪ: " << getNum(a) << endl;
    cout << "bΪ: " << getNum(b) << endl;
    cout << "����" << R << "�������,���Ϊ: " << endl;
    c = add(a, b);
    cout << getNum(c) << endl;
    cout << "����" << R << "�������,���Ϊ: " << endl;
    c = substract(a, b);
    cout << getNum(c) << endl;
    cout << "����" << R << "�������,���Ϊ: " << endl;
    c = multiply(a, b);
    cout << getNum(c) << endl;
    cout << "����" << R << "�������,���Ϊ: " << endl;
    c = divide(a, b);
    cout << getNum(c) << endl;
    cout << "����" << R << "����ȡģ,���Ϊ: " << endl;
    c = mod(a, b);
    cout << getNum(c) << endl;
    return 0;
}