

#include <iostream>
using namespace std;


int main()
{
    //dwunaste
    int n, y, s;
    cout << "Podaj liczbe n:\t";
    cin >> n;
    cout << endl;

    for (int i=0; i <= n; i++)
    {
        cout << "Podaj liczbe:\t";
        cin >> y;
        cout << endl;

    }
    s = y / n;
    cout << "Srednia: \t" << s;
    return 0;

}

