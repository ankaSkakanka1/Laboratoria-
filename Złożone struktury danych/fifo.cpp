#include <iostream>
#include <queue>
#include <ctime>
using namespace std;

int main() {
    int n, m;
    cout << "Podaj n (rozmiar danych): ";
    cin >> n;
    cout << "Podaj m (liczba powtórzeń): ";
    cin >> m;

    queue<int> q;

    // Pomiar czasu dodawania
    clock_t start_add = clock();
    for (int i = 0; i < m; i++) {
        for (int j = 1; j <= n; j++) {
            q.push(j);
        }
        while (!q.empty()) q.pop(); // Czyścimy po każdej iteracji
    }
    clock_t end_add = clock();
    double time_add = (double)(end_add - start_add) / CLOCKS_PER_SEC;
    double avg_add = (time_add / (m * n)) * 1e6; // mikrosekundy

    // Ponownie wypełnij kolejkę do testu DEL
    for (int i = 1; i <= n; i++) {
        q.push(i);
    }

    // Pomiar czasu usuwania
    clock_t start_del = clock();
    for (int i = 0; i < m * n; i++) {
        if (!q.empty()) q.pop();
        else break;
    }
    clock_t end_del = clock();
    double time_del = (double)(end_del - start_del) / CLOCKS_PER_SEC;
    double avg_del = (time_del / (m * n)) * 1e6; // mikrosekundy

    // Wyniki
    cout << "Średni czas dodania elementu [µs]: " << avg_add << endl;
    cout << "Średni czas usunięcia elementu [µs]: " << avg_del << endl;

    return 0;
}
