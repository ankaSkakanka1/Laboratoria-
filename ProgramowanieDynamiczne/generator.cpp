#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(nullptr));
    for (int n = 1; n <= 30; ++n) {
        int X = 4 * n;
        int W1 = X / 2;
        int W2 = (2 * X) / 3;
        int W3 = (3 * X) / 4;

        for (int i = 0; i < 3; ++i) {
            int W = (i == 0) ? W1 : (i == 1) ? W2 : W3;
           // ...existing code...
        std::ofstream out(std::string("dane/test_n") + std::to_string(n) + "_w" + std::to_string(i+1) + ".txt");
// ...existing code...
            out << W << " " << n << "\n";
            for (int j = 0; j < n; ++j) {
                int waga = rand() % X + 1;
                int wartosc = rand() % X + 1;
                out << waga << " " << wartosc << "\n";
            }
        }
    }
    std::cout << "✔ Wygenerowano dane wejściowe\n";
    return 0;
}
