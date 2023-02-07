#include <iostream>

using namespace std;

const int R = 16; // 指定进制
const int bitCount = 4; // R进制的固定位数

/******************************************************************/
/*****自然数的R进制计数法
/******************************************************************/
struct myNumber {
    char bit[bitCount]; // 储存"位"
};

/******************************************************************/
/*****位层次的运算
/******************************************************************/

// 判断一个自然数是否为0
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

// 取符号,a为负数返回true
bool getSign(const myNumber &a) {
    return a.bit[0] >= R / 2;
}

// 比大小,a>=b返回true
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

// 按位取反
myNumber shiftReverse(const myNumber &a) {
    myNumber t;
    for (int i = 0; i < bitCount; i++)
        t.bit[i] = R - a.bit[i] - 1;
    return t;
}

// 左移n位
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

// 左移1位
myNumber shiftLeft(const myNumber &a) {
    return shiftLeft(a, 1);
}

// 右移n位
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

// 右移1位
myNumber shiftRight(const myNumber &a) {
    return shiftRight(a, 1);
}

// 创建一个空的数字
myNumber newZeroNumber() {
    myNumber t;
    for (char &i: t.bit)
        i = 0;
    return t;
}

// 创建一个值为1的数字
myNumber newOneNumber() {
    myNumber t;
    t = newZeroNumber();
    t.bit[bitCount - 1] = 1;
    return t;
}

// 计算进位并左移一位
myNumber carryAdd(const myNumber &a, const myNumber &b) {
    myNumber t;
    for (int i = 1; i < bitCount; i++)
        t.bit[i - 1] = (a.bit[i] + b.bit[i]) / R;
    t.bit[bitCount - 1] = 0;
    return t;
}

// 按位相加但不进位
myNumber bitAdd(const myNumber &a, const myNumber &b) {
    myNumber t;
    for (int i = 0; i < bitCount; i++)
        t.bit[i] = (a.bit[i] + b.bit[i]) % R;
    return t;
}
/******************************************************************/
/*****整数加减乘除
/******************************************************************/
// 自然数加法
myNumber add(const myNumber &a, const myNumber &b) {
    myNumber sum, carry;
    if (isZero(b))
        return a;
    sum = bitAdd(a, b); // 按位相加不进位
    carry = carryAdd(a, b); // 计算进位并左移一位
    return add(sum, carry); // 加进位
}

// 求补码
myNumber unaryMinus(const myNumber &a) {
    myNumber ui, tmp;
    ui = shiftReverse(a);
    tmp = newOneNumber();
    return add(ui, tmp);
}

// 减法
myNumber substract(const myNumber &a, const myNumber &b) {
    return add(a, unaryMinus(b));
}

// 取自然数
myNumber getPositive(const myNumber &a) {
    return getSign(a) ? unaryMinus(a) : a;
}

// 乘法
myNumber multiply(const myNumber &a, const myNumber &b) {
    // 计算符号
    bool flag = true;
    if (getSign(a) == getSign(b))
        flag = false;
    myNumber ua, ub, res /**,tmp*/;
    res = newZeroNumber();
    //tmp = newOneNumber();
    // 取整数的数字部分(自然数)
    ua = getPositive(a);
    ub = getPositive(b);
    // 按自然数乘法计算数字部分
    while (!isZero(ub)) {
//        // 数学定义实现
//        res = add(res, ua);
//        ub = substract(ub, tmp);
        for (int i = 0; i < ub.bit[bitCount - 1]; i++)
            res = add(res, ua);
        // 把ua错位加在积上
        ua = shiftLeft(ua);
        // 从最低位开始依次判断b的每一位
        ub = shiftRight(ub);
    }
    return flag ? unaryMinus(res) : res;
}

// 除法
myNumber *divide1(const myNumber &a, const myNumber &b, myNumber arr[2]) {
    if (isZero(b)) {
        cout << "0不能做除数" << endl;
        return arr;
    }
    // 计算符号
    bool flag = true;
    if (getSign(a) == getSign(b))
        flag = false;
    myNumber ua, ub, quotient, remainder, tmp;
    quotient = newZeroNumber();
    tmp = newOneNumber();
    // 取整数的数字部分(自然数)
    ua = getPositive(a);
    ub = getPositive(b);
    for (int i = bitCount - 1; i >= 0; i--) {
        while (compare(shiftRight(ua, i), ub)) {
            quotient = add(quotient, shiftLeft(tmp, i));
            ua = substract(ua, shiftLeft(ub, i));
        }
    }
//    // 数学定义实现
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

// 求商
myNumber divide(const myNumber &a, const myNumber &b) {
    myNumber *arr = new myNumber[2];
    arr = divide1(a, b, arr);
    return arr[0];
}

// 求模
myNumber mod(const myNumber &a, const myNumber &b) {
    myNumber *arr = new myNumber[2];
    arr = divide1(a, b, arr);
    return arr[1];
}
/******************************************************************/
/*****内部数据于外部数据相互转换举例
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
/*****应用层
/******************************************************************/
int main() {
    myNumber a, b, c;
    char Buffer[30];
    cout << "输入两个" << R << "以内的" << bitCount << "位数." << endl;
    cout << "请输入第一个:";
    cin >> Buffer;
    setNum(a, Buffer);
    cout << "请输入第二个:";
    cin >> Buffer;
    setNum(b, Buffer);
    cout << "a为: " << getNum(a) << endl;
    cout << "b为: " << getNum(b) << endl;
    cout << "按照" << R << "进制相加,结果为: " << endl;
    c = add(a, b);
    cout << getNum(c) << endl;
    cout << "按照" << R << "进制相减,结果为: " << endl;
    c = substract(a, b);
    cout << getNum(c) << endl;
    cout << "按照" << R << "进制相乘,结果为: " << endl;
    c = multiply(a, b);
    cout << getNum(c) << endl;
    cout << "按照" << R << "进制相除,结果为: " << endl;
    c = divide(a, b);
    cout << getNum(c) << endl;
    cout << "按照" << R << "进制取模,结果为: " << endl;
    c = mod(a, b);
    cout << getNum(c) << endl;
    return 0;
}