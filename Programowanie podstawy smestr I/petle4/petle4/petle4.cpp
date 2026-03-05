

#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    //piętnaste
    int n, m;

    cout << "Podaj n:\t\n";
    cin >> n;
    cout << "Podaj m:\t\n";
    cin >> m;

    for (int i = 1; i <= n; i++) {
    
      cout << rand() % m + 0  << endl;
       
    }
    //szesnaste
    int numerek, y=0, a = 0;
    cout << "Podaj szczesliwy numerek z przedzialu [1,10]:\t\n";
    cin >> numerek;

    for (int i = 1; i <= 10; i++) {
        y = rand() % 10 + 1;
        cout << y << endl;
    }
    if (y == numerek) {
        a++;
        cout << "\n\nNumerek jest tyle razy:\n" << a;
    }
   


    

    return 0;
}

