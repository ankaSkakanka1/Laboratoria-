

#include <iostream>
using namespace std;

int main()
{
    //dwunaste
    int n, y, s=0;
    cout << "Podaj liczbe n:\n";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cout << "Podaj y:\n";
        cin >> y;
        s += y;
    } cout << "Średnia :\t" << s/n << endl;

    //trzynaste
    for (int a = 100; a >=0 ; a=a-1) {
        cout << a << endl;
    }

    //czternaste
    int k, l, m;
    cout << "Podaj k:\t";
    cin >> k;
    cout << "Podaj l:\t";
    cin >> l;
    cout << "Podaj m:\t";
    cin >> m;

    cout << "Najmniejsza liczba:\n";
    if (k > l && m > l) {
        cout << l;
    }
    else if (l > m && k > m) {
        cout << m;
    }
    else {
        cout << k;
    }

  





    return 0;
}

