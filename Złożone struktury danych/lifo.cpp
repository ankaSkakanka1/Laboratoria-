#include <iostream>
#include <stack>
#include <ctime>    // Do clock()
#include <iomanip>  // Do std::setprecision

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    stack<int> s;
    clock_t start_add = clock();
    
    for (int i = 0; i < n; ++i) {
        s.push(i);  // Dodajemy dowolną wartość np. i
    }

    clock_t end_add = clock();

    clock_t start_del = clock();

    for (int i = 0; i < m; ++i) {
        if (!s.empty()) {
            s.pop();
        }
    }

    clock_t end_del = clock();

    // Obliczanie czasu w mikrosekundach (1 sek = 1,000,000 µs)
    double add_time = double(end_add - start_add) / CLOCKS_PER_SEC * 1e6;
    double del_time = double(end_del - start_del) / CLOCKS_PER_SEC * 1e6;

    // Średni czas
    double avg_add = n > 0 ? add_time / n : 0;
    double avg_del = m > 0 ? del_time / m : 0;

    cout << fixed << setprecision(4);
    cout << "Sredni czas dodawania: " << avg_add << " µs" << endl;
    cout << "Sredni czas usuwania: " << avg_del << " µs" << endl;

    return 0;
}
