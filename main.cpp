#include <iostream>
#include "MyNumber.h"
#include "MyInt.h"
#include "MyReal.h"

using namespace std;

int main() {
    MyInt a, b, c;
    char Buffer1[30] = "1234";
    char Buffer2[30] = "-567";
    char Buffer[30];
    a.setNum(Buffer1);
    b.setNum(Buffer2);

    cout << "-----整数的加,减,乘,除,取余-----" << endl;
    cout << "按照" << R << "进制相加,结果为: " << endl;
    c = a + b;
    cout << '\t' << a.getNum(Buffer) << endl;
    cout << "+\t" << b.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << c.getNum(Buffer) << endl;

    cout << "按照" << R << "进制相减,结果为: " << endl;
    c = a - b;
    cout << '\t' << a.getNum(Buffer) << endl;
    cout << "-\t" << b.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << c.getNum(Buffer) << endl;

    cout << "按照" << R << "进制相乘,结果为: " << endl;
    c = a * b;
    cout << '\t' << a.getNum(Buffer) << endl;
    cout << "+\t" << b.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << c.getNum(Buffer) << endl;

    cout << "按照" << R << "进制相除,结果为: " << endl;
    c = a / b;
    cout << '\t' << a.getNum(Buffer) << endl;
    cout << "+\t" << b.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << c.getNum(Buffer) << endl;

    cout << "按照" << R << "进制取余,结果为: " << endl;
    c = a % b;
    cout << '\t' << a.getNum(Buffer) << endl;
    cout << "+\t" << b.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << c.getNum(Buffer) << endl;

    cout << "按照" << R << "进制比大小,结果为: " << endl;
    cout << a.getNum(Buffer);
    if (a > b)
        cout << ">";
    else
        cout << "<=";
    cout << b.getNum(Buffer) << endl;

    cout << "\n-----实数的加法,减法,乘法-----" << endl;
    MyInt ad("123456"), ae("3"), bd("-123456"), be("5");
    MyReal d(ad, ae), e(bd, be), f;

    cout << "按照" << R << "进制相加,结果为: " << endl;
    f = d + e;
    cout << '\t' << d.getNum(Buffer) << endl;
    cout << "+\t" << e.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << f.getNum(Buffer) << endl;

    cout << "按照" << R << "进制相减,结果为: " << endl;
    f = d - e;
    cout << '\t' << d.getNum(Buffer) << endl;
    cout << "-\t" << e.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << f.getNum(Buffer) << endl;

    cout << "按照" << R << "进制相乘,结果为: " << endl;
    f = d * e;
    cout << '\t' << d.getNum(Buffer) << endl;
    cout << "*\t" << e.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << f.getNum(Buffer) << endl;
}