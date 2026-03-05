#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime> // zamiast chrono
using namespace std;

int main()
{
    int n;
    cout << "Podaj n: ";
    cin >> n;

    list<int> lst;
    vector<int> values;

    // Dodajemy n liczb (1 do n) do listy
    for (int i = 1; i <= n; i++)
    {
        int x = i;
        values.push_back(x);
        lst.push_back(x); // symulacja komendy "ADD"
    }

    // Tasujemy dane do testowania "FIND"
    shuffle(values.begin(), values.end(), default_random_engine());

    // Pomiar czasu przy użyciu clock()
    int m = 50;
    clock_t start = clock();

    for (int rep = 0; rep < m; rep++)
    {
        for (int x : values)
        {
            find(lst.begin(), lst.end(), x);
        }
    }

    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    double avg_time = duration / (m * n);

    cout << "Średni czas wyszukiwania 1 elementu: " << avg_time*1000000 << endl;

    return 0;
}

