#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#include <iomanip>

std::vector<std::pair<long long, long long>> generate_items(int n, long long X, std::mt19937 &rng) {
    std::vector<std::pair<long long, long long>> items(n);
    std::uniform_int_distribution<int> value_dist(1, 100);

    // Rozdziel wagę X na n dodatnich liczb
    std::vector<long long> weights(n);
    long long remaining = X;
    for (int i = 0; i < n - 1; ++i) {
        weights[i] = rng() % (remaining - (n - i - 1)) + 1;
        remaining -= weights[i];
    }
    weights[n - 1] = remaining;

    // Wypełnij wektor par (waga, wartość)
    for (int i = 0; i < n; ++i) {
        items[i] = {weights[i], value_dist(rng)};
    }

    return items;
}

long long brute_force_knapsack(const std::vector<std::pair<long long, long long>> &items, long long W) {
    int n = items.size();
    long long max_value = 0;

    for (int i = 0; i < (1 << n); ++i) {
        long long current_weight = 0, current_value = 0;
        for (int j = 0; j < n; ++j) {
            if ((i >> j) & 1) {
                current_weight += items[j].first;
                current_value += items[j].second;
            }
        }
        if (current_weight <= W) {
            max_value = std::max(max_value, current_value);
        }
    }

    return max_value;
}

int main() {
    std::ofstream output("wyniki.csv");
    output << "n,X,W,MaxValue,TimeSeconds\n";

    std::mt19937 rng(std::random_device{}());

    for (int n = 2; n <= 30; ++n) {
        for (int k : {4, 6, 8}) {
            long long X = k * n;
            for (double w_factor : {0.5, 2.0/3.0, 0.75}) {
                long long W = static_cast<long long>(X * w_factor);

                auto items = generate_items(n, X, rng);

                auto start = std::chrono::high_resolution_clock::now();
                long long max_val = brute_force_knapsack(items, W);
                auto end = std::chrono::high_resolution_clock::now();

                std::chrono::duration<double> elapsed = end - start;

                output << n << "," << X << "," << W << "," << max_val << "," 
                       << std::fixed << std::setprecision(6) << elapsed.count() << "\n";

                std::cout << "n=" << n << " X=" << X << " W=" << W 
                          << " Max=" << max_val << " Time=" << elapsed.count() << "s\n";
            }
        }
    }

    output.close();
    return 0;
}
