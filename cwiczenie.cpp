#include <stdio.h>
#include <iostream>
using namespace std;

class Class1
{
protected:
    int field1;

public:
    Class1(int x = 1) { field1 = x; }
    void f() { field1 += 2; }
    virtual void g() { field1++; }
    int h()
    {
        f();
        return field1;
    }
    int j()
    {
        g();
        return field1;
    }
};
class Class2 : public Class1
{
private:
    int field2;

public:
    Class2(int x = 5) { field2 = x; }
    void f() { field2 += 6; }
    void g() { field1 += 2; }
};
/*class KB{
    public:
    static int PoleKBaz;
};
int KB::PoleKBaz = 0;
class KP: public KB{
    public:
    int a;
};*/

int main()
{
    Class1 class1;
    Class2 class2;
    cout << class1.h();
    cout << class1.j();
    cout << class2.h();
    cout << class2.j();
    return 0;
}
