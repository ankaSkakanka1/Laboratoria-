
#include <iostream>
using namespace std;

int main()
{
    //ósme
    for (int i=1; i <= 100; i++)
    {
        if (i % 2 == 0)
            cout << i << endl;
    }

    //dziesiąte
    int n;
    int y = 0;
    cout << "Podaj liczbe n : \n";
    cin >> n;
    for (int i = 0; i <= 100; i++)
    {
        if (i % n == 0)
        {
            y++;

        }
    }cout << "Wynik :" << y - 1 << endl;

    //dziewiąte
   
    for (int i=1 ; i <= 100; i++)
    {
        if (i % n == 0)
            cout << i << endl;
    }

    //jedenaste

    int a, b, i;
    cout << "Podaj liczbe a:\n";
    cin >> a;
    cout << "Podaj liczbe b:\n";
    cin >> b;

    for (i = a; b > i; i++)
    {
        if (i % 3 == 0)
            cout << i << endl;
    }

    for (i = b; a > i; i++)
    {
        if (i % 3 == 0)
            cout << i << endl;
    }

    




    return 0;
}


