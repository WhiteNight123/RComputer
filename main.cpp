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

    cout << "-----�����ļ�,��,��,��,ȡ��-----" << endl;
    cout << "����" << R << "�������,���Ϊ: " << endl;
    c = a + b;
    cout << '\t' << a.getNum(Buffer) << endl;
    cout << "+\t" << b.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << c.getNum(Buffer) << endl;

    cout << "����" << R << "�������,���Ϊ: " << endl;
    c = a - b;
    cout << '\t' << a.getNum(Buffer) << endl;
    cout << "-\t" << b.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << c.getNum(Buffer) << endl;

    cout << "����" << R << "�������,���Ϊ: " << endl;
    c = a * b;
    cout << '\t' << a.getNum(Buffer) << endl;
    cout << "+\t" << b.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << c.getNum(Buffer) << endl;

    cout << "����" << R << "�������,���Ϊ: " << endl;
    c = a / b;
    cout << '\t' << a.getNum(Buffer) << endl;
    cout << "+\t" << b.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << c.getNum(Buffer) << endl;

    cout << "����" << R << "����ȡ��,���Ϊ: " << endl;
    c = a % b;
    cout << '\t' << a.getNum(Buffer) << endl;
    cout << "+\t" << b.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << c.getNum(Buffer) << endl;

    cout << "����" << R << "���Ʊȴ�С,���Ϊ: " << endl;
    cout << a.getNum(Buffer);
    if (a > b)
        cout << ">";
    else
        cout << "<=";
    cout << b.getNum(Buffer) << endl;

    cout << "\n-----ʵ���ļӷ�,����,�˷�-----" << endl;
    MyInt ad("123456"), ae("3"), bd("-123456"), be("5");
    MyReal d(ad, ae), e(bd, be), f;

    cout << "����" << R << "�������,���Ϊ: " << endl;
    f = d + e;
    cout << '\t' << d.getNum(Buffer) << endl;
    cout << "+\t" << e.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << f.getNum(Buffer) << endl;

    cout << "����" << R << "�������,���Ϊ: " << endl;
    f = d - e;
    cout << '\t' << d.getNum(Buffer) << endl;
    cout << "-\t" << e.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << f.getNum(Buffer) << endl;

    cout << "����" << R << "�������,���Ϊ: " << endl;
    f = d * e;
    cout << '\t' << d.getNum(Buffer) << endl;
    cout << "*\t" << e.getNum(Buffer) << endl;
    cout << "---------------------------" << endl;
    cout << '\t' << f.getNum(Buffer) << endl;
}